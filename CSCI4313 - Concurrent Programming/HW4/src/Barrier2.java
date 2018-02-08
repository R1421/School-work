
public class Barrier2 extends Barrier {

	private Boolean[] A;
	public Barrier2(int n) {
		super(n);
		A = new Boolean[n];
		for(int i = 0; i < n; i++){
			A[i] = false;
		}
	}
	
	public void runBarrier(){
		int i = (int)Thread.currentThread().getId() % n;
		if(i == 0){
			A[i] = true;
		} else {
			while(A[i - 1] == false){
//				try {
//					Thread.sleep(20);
//				} catch (InterruptedException e) {
//					// TODO Auto-generated catch block
//					e.printStackTrace();
//				}
			}
			A[i] = true;
		}
		while(A[n-1] == false){}
	}

}
