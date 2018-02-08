import java.util.concurrent.locks.*;

public class SavingsAccount {

	private int balance;
	private int priorityNum;
	private Lock lock;
	
	public SavingsAccount(int b){
		balance = b;
		priorityNum = 0;
		lock = new ReentrantLock();
	}
	
	public int getBalance(){
		return balance;
	}
	
	public void deposit(int k){
		lock.lock();
		balance += k;
		lock.unlock();
		System.out.println("Deposited: " + k + ", Balance: " + balance);
	}
	
	public void withdraw(int k, boolean priority){
		boolean finished = false;
		while(!finished){
			lock.lock();
			if(k <= balance){
				balance -= k;
				finished = true;
				System.out.println("Withdrew: " + k + ", Balance: " + balance);
			}
			lock.unlock();
//			try {
//				Thread.sleep(10);
//			} catch (InterruptedException e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			}
		}
		
	}
}
