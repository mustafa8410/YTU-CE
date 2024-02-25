package lab2b;

public class Iett {
	private Otobus[] otobusler;
	
	public Iett(int otobusSayisi) {
		otobusler = new Otobus[otobusSayisi];
	}
	
	public boolean otobusBin(Kisi k, Durak d) {
		int i,j;
		for(i=0;i<otobusler.length;i++) {
			if(otobusler[i] != null) {
				Durak[] duraklar = otobusler[i].getDuraklar();
				for(j=0;j<duraklar.length;j++) {
					if(duraklar[j] != null && duraklar[j] == d) {
						if(k.odemeYap(otobusler[i].getDurakSayisi())) {
							System.out.println(otobusler[i].getOtobusNo() + "otobusune bindiniz.");
							return true;
						}
						
						else {
							return false;
						}
					}
				}

			}
		}
		System.out.println("Boyle bir durak yok.");
		return false;
	}
	
	public void tumOtobusleriGoster() {
		int i;
		for(i=0;i<otobusler.length;i++) {
			if(otobusler[i] != null) {
				System.out.println(i + ". otobus:");
				otobusler[i].duraklariGoster();
			}
		}
	}
	
	public void otobusEkle(Otobus o) {
		int i=0;
		while(i<otobusler.length && otobusler[i] != null)
			i++;
		if(i<otobusler.length) {
			otobusler[i] = o;
			System.out.println("Basariyla eklendi.");
		}
		else {
			System.out.println("Yer yok.");
		}
	}
	
	
	
}
