package lab2b;

public class AnonimKisi extends Kisi{

	public AnonimKisi(String ad, int id, double bakiye) {
		super(ad, id, bakiye);
		// TODO Auto-generated constructor stub
	}
	
	public boolean odemeYap(int durakSayisi) {
		int tutar;
		tutar = durakSayisi * getBirimUcret();
		if(getBakiye() < tutar) {
			System.out.println("Yeterli bakiyeniz yok.");
			return false;
		}
		else {
			setBakiye(getBakiye() - tutar);
			System.out.println("Odeme gerceklesti.");
			return true;
		}
	}
}
