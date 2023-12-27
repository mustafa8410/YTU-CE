package lab2b;

public class Durak {
	private int durakKodu;

	public Durak(int durakKodu) {
		super();
		this.durakKodu = durakKodu;
	}

	public int getDurakKodu() {
		return durakKodu;
	}

	@Override
	public String toString() {
		return "Durak [durakKodu=" + durakKodu + "]";
	}
	
	
}
