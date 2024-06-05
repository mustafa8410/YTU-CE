import sys
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import numpy as np
from PyQt5 import QtWidgets
from PyQt5 import uic

class appUI(QtWidgets.QMainWindow):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        self.ui = uic.loadUi('gui.ui',self)

        self.t = np.linspace(0,10,100)

        self.figure = Figure()
        self.canvas = FigureCanvas(self.figure)

        plotwidget = self.findChild(QtWidgets.QWidget,'widget')
        layout = QtWidgets.QVBoxLayout(plotwidget)
        layout.addWidget(self.canvas)

        plotButton1 = self.findChild(QtWidgets.QPushButton,'pushButton')
        plotButton1.clicked.connect(self.plotAll)
        plotButton2 = self.findChild(QtWidgets.QPushButton,'pushButton_2')
        plotButton2.clicked.connect(self.plotFourier)

    def plotAll(self):
        try:
            a1 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit').text())
            a2 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_2').text())
            a3 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_3').text())
            b1 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_12').text())
            b2 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_18').text())
            b3 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_13').text())
            cos1_phase = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_4').text())
            cos2_phase = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_5').text())
            cos3_phase = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_6').text())
            sin1_phase = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_11').text())
            sin2_phase = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_14').text())
            sin3_phase = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_15').text())
            cos1_frequency = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_7').text())
            cos2_frequency = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_8').text())
            cos3_frequency = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_9').text())
            sin1_frequency = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_17').text())
            sin2_frequency = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_10').text())
            sin3_frequency = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_16').text())
        except ValueError:
            QtWidgets.QMessageBox.warning(self,'Missing Input', "Every needed input should be given correctly!")
            return


        cos1 = a1 * np.cos(cos1_frequency * 2 * np.pi * self.t + cos1_phase)
        cos2 = a2 * np.cos(cos2_frequency * 2 * np.pi * self.t + cos2_phase)
        cos3 = a3 * np.cos(cos3_frequency * 2 * np.pi * self.t + cos3_phase)
        sin1 = b1 * np.sin(sin1_frequency * 2 * np.pi * self.t + sin1_phase)
        sin2 = b2 * np.sin(sin2_frequency * 2 * np.pi * self.t + sin2_phase)
        sin3 = b3 * np.sin(sin3_frequency * 2 * np.pi * self.t + sin3_phase)
        addition = cos1 + cos2 + cos3 + sin1 + sin2 + sin3

        self.figure.clear()

        ax1 = self.figure.add_subplot(411)
        ax1.plot(self.t,cos1,label='cosine',linestyle='-',color='b')
        ax1.plot(self.t,sin1,label='sine',linestyle='--',color='r')
        ax1.set_title("Sine-Cosine 1")

        ax2 = self.figure.add_subplot(412)
        ax2.plot(self.t, cos2, label='cosine', linestyle='-', color='b')
        ax2.plot(self.t, sin2, label='sine', linestyle='--', color='r')
        ax2.set_title("Sine-Cosine 2")

        ax3 = self.figure.add_subplot(413)
        ax3.plot(self.t, cos3, label='cosine', linestyle='-', color='b')
        ax3.plot(self.t, sin3, label='sine', linestyle='--', color='r')
        ax3.set_title("Sine-Cosine 3")

        ax4 = self.figure.add_subplot(414)
        ax4.plot(self.t, addition)
        ax4.set_title("Addition of All")

        self.figure.tight_layout()
        ax1.legend()
        ax2.legend()
        ax3.legend()
        self.canvas.draw()





    def plotFourier(self):
        try:
            a0 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_19').text())
            a1 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit').text())
            a2 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_2').text())
            a3 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_3').text())
            b1 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_12').text())
            b2 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_18').text())
            b3 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_13').text())
            w0 = float(self.findChild(QtWidgets.QLineEdit, 'lineEdit_20').text())
        except ValueError:
            QtWidgets.QMessageBox.warning(self, 'Missing Input', "Every needed input should be given correctly!")
            return

        signal = a0 + a1 * np.cos(1 * w0 * self.t) + b1 * np.sin(1 * w0 * self.t) + a2 * np.cos(2 * w0 * self.t) + b2 * np.sin(2 * w0 * self.t) + a3 * np.cos(3 * w0 * self.t) + b3 * np.sin(3 * w0 * self.t)
        self.figure.clear()

        ax = self.figure.add_subplot(111)
        ax.plot(self.t,signal)
        ax.set_xlabel('Time')
        ax.set_ylabel('Fourier Signal')

        self.canvas.draw()



app = QtWidgets.QApplication([])
mainWindow = appUI()
mainWindow.show()
sys.exit(app.exec_())