import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.*;

public class Barrier1 extends Barrier {
	private AtomicInteger counter;
	private Lock lock = new ReentrantLock();
	private Condition barrier = lock.newCondition();
	
	public Barrier1(int n){
		super(n);
		counter = new AtomicInteger(0);
	}
	
//	public void runBarrier(){
//		counter.incrementAndGet();
//		while(counter.get() != n){
//			try {
//				barrier.await();
//			} catch (InterruptedException e) {
//				e.printStackTrace();
//			} 
//		}
//		barrier.signalAll();
//		return;
//	}
	
//	public void runBarrier(){
//		lock.lock();
//		try {
//			counter.incrementAndGet();
//			while(counter.get() != n){
//				barrier.await();
//			}
//		} catch (InterruptedException e) {
//			e.printStackTrace();
//		} finally {
//			barrier.signalAll();
//			lock.unlock();
//		}
//	}
	
	public void runBarrier(){
		lock.lock();
		counter.incrementAndGet();
		lock.unlock();
		while(counter.get() != n){}
	}
}
