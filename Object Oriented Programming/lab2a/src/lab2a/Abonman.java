package lab2a;

public class Abonman extends Kisi {
	private int kredi;

	public Abonman(String ad, int id, double bakiye, int kredi) {
		super(ad, id, bakiye);
		this.kredi = kredi;
	}

	public int getKredi() {
		return kredi;
	}

	public void setKredi(int kredi) {
		this.kredi = kredi;
	}

	
	public boolean odemeYap(double ucret) {
		if(kredi >=5) {
			kredi = kredi-5;
			return true;
		}
		else if(getBakiye() >= ucret) {
			setBakiye(getBakiye() - ucret);
			kredi++;
			return true;
		}
		else {
			return false;
		}
	}
	
	
}
