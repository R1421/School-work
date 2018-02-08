import java.util.concurrent.atomic.AtomicInteger;

public class DanceCompetition {	

	private LockFreeStack stack = new LockFreeStack();
	private static AtomicInteger girlCount = new AtomicInteger(0);

	public static void main(String[] args) {
		LockFreeStack stack = new LockFreeStack();
		Thread[] thread = new Thread[40];
		Pair[] pairs = new Pair[20];
		for(int i = 0; i < 20; i++){
			pairs[i] = new Pair();
		}
		for(int i = 0; i < 20; i++){
			final int grade = i%5 + 6;
			thread[i] = new Thread(new Runnable(){
				public void run(){
					int value = girlCount.getAndIncrement();
					stack.push(value, grade);
					pairs[value].setGirl((int) Thread.currentThread().getId());
				}
			});
		}
		for(int i = 20; i < 40; i++){
			final int grade = i%5+6;
			thread[i] = new Thread(new Runnable(){
				public void run(){
					pairs[stack.pop(grade)].setBoy((int) Thread.currentThread().getId());
				}
			});
		}
		for(Thread threadI: thread){
			threadI.start();
		}
		for(Thread threadI: thread){
			try {
				threadI.join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		for(Pair p: pairs){
			p.printPair();
		}
	}

}
