import matplotlib.pyplot as plt
import numpy as np
import sounddevice as sd
from datetime import datetime
import scipy.io.wavfile as wav

# convolution formula: y[n] = [in addition symbol, k in range of (-inf, +inf)] x[k] . h[n-k]


def myconv(x, xZeroPoint, h, hZeroPoint):
    h.reverse()  # h[k] -> h[-k]
    maxLength = len(x) + len(h) - 1  # y bundan buyuk olamaz daha kucuk olabilir tabi ama o zaman ekstra kisimlar 0 olur
    y = [0]
    global yZeroPoint
    yZeroPoint = 0
    for i in range(maxLength - 1):
        y.append(0)
    # tersini alip otelemeye baslayinca ilk bulusma, b[-k]'nin (xZeroPoint + hZeropoint) kadar saga otelenmis halinde
    for n in range(maxLength):
        realN = n - (xZeroPoint + hZeroPoint)
        if realN == 0:
            yZeroPoint = n  # h[-k]'nin hic otelenmedigi indis
        for k in range(len(x)):
            h_overlap = (len(h)-1) - realN - xZeroPoint + k
            if h_overlap >= 0 and h_overlap < len(h):
                y[n] += x[k] * h[h_overlap]
    h.reverse() # return h[-k] back to h[k]
    return y


# test case 1
x = [1,2,3]
xZero = 1
h = [1, 2, 3]
hZero = 0
print("Test case 1\nx[n] = ", x, "x zero = ", xZero, "\nh[m] = ", h, "h zero = ", hZero)
y = myconv(x, xZero, h, hZero)
print("My convolution's output:")
print("y[n] = ", y,  "y zero = ", yZeroPoint)
print("Built-in convolution's output:")
yNP = np.convolve(x,h)
print("y[n] = ", yNP, "y zero = ", yZeroPoint)
n = [-1, 0, 1]
plt.subplot(4,1,1)
plt.stem(n,x)
plt.xlabel("n")
plt.ylabel("x[n]")
n = [0, 1, 2]
plt.subplot(4,1,2)
plt.stem(n,h)
plt.xlabel("m")
plt.ylabel("h[m]")
n.clear()
for i in range(0 - yZeroPoint,len(y) - yZeroPoint):
    n.append(i)
plt.subplot(4,1,3)
plt.stem(n,y)
plt.xlabel("n")
plt.ylabel("myConv[n]")
plt.subplot(4,1,4)
plt.stem(n,yNP)
plt.xlabel("n")
plt.ylabel("built-in[n]")
plt.tight_layout()
plt.show()

# test case 2
x = [2, 2, 1]
xZero = 0
h = [3, 3, 3, 3, 3]
hZero = 0
print("Test case 2\nx[n] = ", x, "x zero = ", xZero, "\nh[m] = ", h, "h zero = ", hZero)
y = myconv(x, xZero, h, hZero)
print("My convolution's output:")
print("y[n] = ", y,  "y zero = ", yZeroPoint)
print("Built-in convolution's output:")
yNP = np.convolve(x,h)
print("y[n] = ", yNP, "y zero = ", yZeroPoint)
n = [0, 1, 2]
plt.subplot(4,1,1)
plt.stem(n,x)
plt.xlabel("n")
plt.ylabel("x[n]")
n.append(3)
n.append(4)
plt.subplot(4,1,2)
plt.stem(n,h)
plt.xlabel("m")
plt.ylabel("h[m]")
n.clear()
for i in range(0 - yZeroPoint,len(y) - yZeroPoint):
    n.append(i)
plt.subplot(4,1,3)
plt.stem(n,y)
plt.xlabel("n")
plt.ylabel("myConv[n]")
plt.subplot(4,1,4)
plt.stem(n,yNP)
plt.xlabel("n")
plt.ylabel("built-in[n]")
plt.tight_layout()
plt.show()

# free the previous variables

x.clear()
n.clear()
y.clear()
xZero = None
hZero = None
yZeroPoint = None

# audio recording
duration = 5
input("\n\n\nPress Enter to start speaking for 5 seconds: ")
print("Speaking for 5 seconds...")
x1 = sd.rec(int(duration * 8820), samplerate= 8820, channels=1, dtype='float32')
sd.wait()
print("Speaking finished.")
print("The audio you recorded:")
sd.play(x1,samplerate=8820)
sd.wait()
duration = 10
input("Press Enter to start speaking for 10 seconds: ")
print("Speaking for 10 seconds...")
x2 = sd.rec(int(duration * 8820), samplerate= 8820, channels=1, dtype='float32')
sd.wait()
print("Speaking finished.")
print("The audio you recorded:\n\n")
sd.play(x2,samplerate=8820)
sd.wait()
x1 = x1.flatten()
x2 = x2.flatten()
# question 4
input("Press Enter to start the Section 4: ")


def yn_impulse_response(M):
    response_length = (M * 3000) + 1
    impulse_response = [0.0] * response_length
    for n in range(0, response_length, 3000):
        response = 0
        for k in range(1,M+1):
            if (n - 3000 * k) == 0:
                response += pow(2, (0-k)) * k
        if n == 0:
            response += 1
        impulse_response[n] = response
    return impulse_response


print("Calculating the impulse responses...")
h_m3 = yn_impulse_response(3) # impulse response when M = 3
h_m4 = yn_impulse_response(4) # impulse response when M = 4
h_m5 = yn_impulse_response(5) # impulse response when M = 5

print("Calculation completed.")
input("Press Enter to start the convolutions. All results will be saved, you can listen later. ")
# now we put these responses to convolution with the recorded audios
# M = 3
# 5 second audio
print("Calculating scenario 1: M = 3, 5 second audio...")
print("Calculating myconv...")
print("Started at: ",datetime.now().hour, ':', datetime.now().minute)
y = myconv(x1,0,h_m3,0)
print("Calculation completed.")
print("Ended at: ", datetime.now().hour, ':', datetime.now().minute)
print("My convolution result:")
sd.play(y, samplerate=8820)
sd.wait()
y = np.array(y, dtype=np.float32)
wav.write("y5_myConv_m3.wav",8820,y)
print("Calculating built-in convolution...")
print("Started at: ", datetime.now().hour, ':', datetime.now().minute)
y = np.convolve(x1,h_m3)
print("Calculation completed.")
print("Ended at: ", datetime.now().hour, ':', datetime.now().minute)
print("Built-in convolution result:\n\n")
sd.play(y, samplerate=8820)
sd.wait()
y = np.array(y, dtype=np.float32)
wav.write("y5_built_m3.wav",8820,y)
# 10 second audio
print("Calculating scenario 2: M = 3, 10 second audio...")
print("Calculating myconv...")
print("Started at: ",datetime.now().hour, ':', datetime.now().minute)
y = myconv(x2,0,h_m3,0)
print("Calculation completed.")
print("Ended at: ", datetime.now().hour, ':', datetime.now().minute)
print("My convolution result:")
sd.play(y, samplerate=8820)
sd.wait()
y = np.array(y, dtype=np.float32)
wav.write("y10_myConv_m3.wav",8820,y)
print("Calculating built-in convolution...")
print("Started at: ", datetime.now().hour, ':', datetime.now().minute)
y = np.convolve(x2,h_m3)
print("Calculation completed.")
print("Ended at: ", datetime.now().hour, ':', datetime.now().minute)
print("Built-in convolution result:\n\n")
sd.play(y, samplerate=8820)
sd.wait()
y = np.array(y, dtype=np.float32)
wav.write("y10_built_m3.wav",8820,y)
# M = 4
# 5 second audio
print("Calculating scenario 3: M = 4, 5 second audio...")
print("Calculating myconv...")
print("Started at: ",datetime.now().hour, ':', datetime.now().minute)
y = myconv(x1,0,h_m4,0)
print("Ended at: ",datetime.now().hour, ':', datetime.now().minute)
print("Calculation completed.")
print("My convolution result:")
sd.play(y, samplerate=8820)
sd.wait()
y = np.array(y, dtype=np.float32)
wav.write("y5_myConv_m4.wav",8820,y)
print("Calculating built-in convolution...")
print("Started at: ",datetime.now().hour, ':', datetime.now().minute)
y = np.convolve(x1,h_m4)
print("Calculation completed.")
print("Ended at: ",datetime.now().hour, ':', datetime.now().minute)
print("Built-in convolution result:\n\n")
sd.play(y, samplerate=8820)
sd.wait()
y = np.array(y, dtype=np.float32)
wav.write("y5_built_m4.wav",8820,y)
# 10 second audio
print("Calculating scenario 4: M = 4, 10 second audio...")
print("Calculating myconv...")
print("Started at: ",datetime.now().hour, ':', datetime.now().minute)
y = myconv(x2,0,h_m4,0)
print("Calculation completed.")
print("Ended at: ",datetime.now().hour, ':', datetime.now().minute)
print("My convolution result:")
sd.play(y, samplerate=8820)
sd.wait()
y = np.array(y, dtype=np.float32)
wav.write("y10_myConv_m4.wav",8820,y)
print("Calculating built-in convolution...")
print("Started at: ",datetime.now().hour, ':', datetime.now().minute)
y = np.convolve(x2,h_m4)
print("Calculation completed.")
print("Ended at: ",datetime.now().hour, ':', datetime.now().minute)
print("Built-in convolution result:\n\n")
sd.play(y, samplerate=8820)
sd.wait()
y = np.array(y, dtype=np.float32)
wav.write("y10_built_m4.wav",8820,y)
# M = 5
# 5 second audio
print("Calculating scenario 5: M = 5, 5 second audio...")
print("Calculating myconv...")
print("Started at: ",datetime.now().hour, ':', datetime.now().minute)
y = myconv(x1,0,h_m5,0)
print("Calculation completed.")
print("Ended at: ",datetime.now().hour, ':', datetime.now().minute)
print("My convolution result:")
sd.play(y, samplerate=8820)
sd.wait()
y = np.array(y, dtype=np.float32)
wav.write("y5_myConv_m5.wav",8820,y)
print("Calculating built-in convolution...")
print("Started at: ",datetime.now().hour, ':', datetime.now().minute)
y = np.convolve(x1,h_m5)
print("Calculation completed.")
print("Ended at: ",datetime.now().hour, ':', datetime.now().minute)
print("Built-in convolution result:\n\n")
sd.play(y, samplerate=8820)
sd.wait()
y = np.array(y, dtype=np.float32)
wav.write("y5_built_m5",8820,y)
# 10 second audio
print("Calculating scenario 6: M = 5, 10 second audio...")
print("Calculating myconv...")
print("Started at: ",datetime.now().hour, ':', datetime.now().minute)
y = myconv(x2,0,h_m5,0)
print("Calculation completed.")
print("Ended at: ",datetime.now().hour, ':', datetime.now().minute)
print("My convolution result:")
sd.play(y, samplerate=8820)
sd.wait()
y = np.array(y, dtype=np.float32)
wav.write("y10_myConv_m5",8820,y)
print("Calculating built-in convolution...")
print("Started at: ",datetime.now().hour, ':', datetime.now().minute)
y = np.convolve(x2,h_m5)
print("Calculation completed.")
print("Ended at: ",datetime.now().hour, ':', datetime.now().minute)
print("Built-in convolution result:\n\n")
sd.play(y, samplerate=8820)
sd.wait()
y = np.array(y, dtype=np.float32)
wav.write("y10_built_m5",8820,y)





