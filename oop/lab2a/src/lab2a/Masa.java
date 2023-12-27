package lab2a;

public class Masa {
	private Sandalye[] sandalyeler;

	
	
	
	public Masa() {
		super();
		this.sandalyeler = new Sandalye[3];
	}


	public Sandalye[] getSandalyeler() {
		return sandalyeler;
	}


	public void sandalyeEkle(Sandalye s) {
		int i=0;
		while (i<2) {
			if(sandalyeler[i] != null)
				i++;
			else {
				sandalyeler[i] = s;
			}
		}
	}

	public void sandalyeEkle(Sandalye s, int sira) {
		if(sandalyeler[sira] != null)
			System.out.println("masada yer olmadigi icin sandalye eklenemiyor.");
		else {
			sandalyeler[sira] = s;
		}
			
	}
	
	public void sandalyeSil(Sandalye s) {
		int i=0;
		while(i<2) {
			if(sandalyeler[i] == s) {
				sandalyeler[i] = null;
				System.out.println("Sandalye silme islemi gerceklesti.");
			}
			else {
				i++;
			}
		}
	}
	
	public void masaDolulukGoster() {
		int i;
		for(i=0;i<sandalyeler.length;i++) {
			System.out.println(sandalyeler[i]);
		}
			
	}
	
	
	
	
	
}
	

