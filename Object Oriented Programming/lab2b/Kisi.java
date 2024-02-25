package lab2b;

public abstract class Kisi {
	private String ad;
	private int id;
	private double bakiye;
	private final int birimUcret = 2;
	
	
	public Kisi(String ad, int id, double bakiye) {
		super();
		this.ad = ad;
		this.id = id;
		this.bakiye = bakiye;
	}


	public double getBakiye() {
		return bakiye;
	}


	public void setBakiye(double bakiye) {
		this.bakiye = bakiye;
	}


	public int getBirimUcret() {
		return birimUcret;
	}
	
	public abstract boolean odemeYap(int durakSayisi);
	
	
	
	
}
