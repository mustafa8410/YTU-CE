package lab2a;

public class KitapKafe {
	private Masa[] masalar;
	
	public KitapKafe(int masaSayisi) {
		this.masalar = new Masa[masaSayisi];
	}
	
	public void masaEkle(Masa m) {
		int i=0;
		while(i<masalar.length && masalar[i] != null)
			i++;
		if(i!=masalar.length)
			masalar[i] = m;
		
	}
	
	public boolean yerAyir(Kisi k) {
		int i, j;
		for(i=0;i<masalar.length;i++) {
			Sandalye[] sandalyeler = masalar[i].getSandalyeler();
			for(j=0;j<sandalyeler.length;j++) {
				if(sandalyeler[j] != null && !sandalyeler[i].isDoluluk()) {
					if(k.odemeYap(sandalyeler[j].getUcret())) {
						sandalyeler[j].setDoluluk(true);
            			System.out.println(i + ".masa "+ j +".sandalyeye atandınız");
            			return true;
					}
					else {
                        System.out.println("Bakiye Yetersiz.");
                        return false;
					}
				}
			}

		}
		System.out.println("Bos Masa Yok");
        return false;
				
	
	
	}
	public void tumMasalariGoster() {
		int i;
		for(i=0;i<masalar.length;i++) {
			if(masalar[i] != null) {
				System.out.println(i + ". masa");
				masalar[i].masaDolulukGoster();
			}
		}
	}
	
	
	
}
