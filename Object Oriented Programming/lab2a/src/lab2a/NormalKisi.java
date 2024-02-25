package lab2a;

public class NormalKisi extends Kisi {

	public NormalKisi(String ad, int id, double bakiye) {
		super(ad, id, bakiye);
	}
	
	
	public boolean odemeYap(double ucret) {
		if(getBakiye() >= ucret) {
			setBakiye(getBakiye() - ucret);
			return true;
		}
		else {
			return false;
		}
	}
}
