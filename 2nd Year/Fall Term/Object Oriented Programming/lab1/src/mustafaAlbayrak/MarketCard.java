package mustafaAlbayrak;
public class MarketCard {
	private int cardNo;



	private double points;
	
	
	public MarketCard(int cardNo) {
		this.cardNo = cardNo;
	}
	
	public void addPoints(double point) {
		this.points = this.points + point;
	}
	public int getCardNo() {
		return cardNo;
	}

	public double getPoints() {
		return points;
	}
	
	
	
}
