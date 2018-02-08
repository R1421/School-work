
public class Pair {
	private int girl;
	private int boy;
	
	public Pair(){
		girl = -1;
		boy = -1;
	}
	
	public void setGirl(int girl){
		this.girl = girl;
	}
	
	public void setBoy(int boy){
		this.boy = boy;
	}
	
	public void printPair(){
		System.out.println("Girl: " + girl + " and Boy: " + boy);
	}
}
