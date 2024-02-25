package lab2b;

public class IndirimliKisi extends Kisi {
	private int kredi;

	public IndirimliKisi(String ad, int id, double bakiye, int kredi) {
		super(ad, id, bakiye);
		this.kredi = kredi;
	}
	
	public boolean odemeYap(int durakSayisi) {
		int tutar;
		tutar = getBirimUcret() * durakSayisi;
		if(kredi >= tutar) {
			kredi = kredi - tutar;
			System.out.println("Odeme krediyle gerceklesti.");
			return true;
		}
		else {
			if(getBakiye() >= tutar) {
				setBakiye(getBakiye() - tutar);
				kredi = kredi + durakSayisi;
				System.out.println("Odeme bakiyeyle gerceklesti.");
				return true;
			}
			else {
				System.out.println("Yeterli bakiye yok.");
				return false;
			}
		}
	}

	public int getKredi() {
		return kredi;
	}

	public void setKredi(int kredi) {
		this.kredi = kredi;
	}

	@Override
	public String toString() {
		return "IndirimliKisi [kredi=" + kredi + "]";
	}
	
	
}
