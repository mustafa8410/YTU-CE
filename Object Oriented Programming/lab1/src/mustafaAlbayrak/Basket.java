package mustafaAlbayrak;

public class Basket {
	private int ID;
	Item items[] = new Item[2];
	MarketCard card;
	
	
	public Basket(int iD) {
		this.ID = iD;
	}
	
	public void addItem(Item anItem) {
		int i = 0;
		while(i < 1 && items[i] != null) {
			i++;
		}
		if(i <= 1 && items[i] == null) {
			items[i] = anItem;
		}
		else {
			System.out.println("You've reached the maximum amount of items in your basket.");
		}
			
			
	}
	
	public void basketInfo() {
		int counter = 0;
		double totprice = 0;
		for (int i=0; i<2; i++) {
			if(items[i] != null) {
				counter++;
				totprice = totprice + items[i].getPrice();
				
			}
		}
		System.out.println("Basket ID: " + ID );
		System.out.println("Number of items in the basket: " + counter);
		System.out.println("Total price: " + totprice);
		
		totprice = totprice / 10;
		card.addPoints(totprice);
		
		
		
	}

	public void setCard(MarketCard card) {
		this.card = card;
	}
	
	


}
