package lab2b;

public class Otobus {
	private int otobusNo;
	private Durak[] duraklar;
	
	public Otobus(int otobusNo) {
		super();
		this.otobusNo = otobusNo;
		duraklar = new Durak[3];
	}

	public int getOtobusNo() {
		return otobusNo;
	}

	public Durak[] getDuraklar() {
		return duraklar;
	}
	
	public int getDurakSayisi() {
		return duraklar.length;
	}
	
	public void durakEkle(Durak d) {
		int i = 0;
		while (i < duraklar.length && duraklar[i] != null)
			i++;

		if (i != duraklar.length)
			duraklar[i] = d;
		else
			System.out.println("yer olmadıgı ıcın durak eklenemiyor.");
	}
	public void durakEkle(Durak d, int sira) {
		if(duraklar[sira] == null) {
			duraklar[sira] = d;
		}
		else {
			System.out.println("Secilen sirada zaten bir durak var.");
		}
	}
	
	public void durakSil(Durak d) {
		int i=0;
		while(i<duraklar.length && duraklar[i] != d)
			i++;
		if(duraklar[i] == d) {
			duraklar[i] = null;
			System.out.println("Durak silme islemi gerceklesti.");
		}
		else {
			System.out.println("Boyle bir durak yok.");
		}
	}
	
	public void duraklariGoster() {
		int i;
		for(i=0;i<duraklar.length;i++) {
			System.out.println(duraklar[i]);
	}
	}
	
	
	
	
	
}
