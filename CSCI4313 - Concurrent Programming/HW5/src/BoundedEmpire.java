import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.*;

public class BoundedEmpire implements Empire {
	//Implements bounded concurrent queue
	
	/*
	 * Code altered from Herlihy and Shavit - The art of multiprocessor programming; Chapter 10.3
	 */
	
	private BattleResult result;
	private boolean battling;
	private Lock battleLock = new ReentrantLock();
	
	public class Node{
		public Node next;
		
		Node(){}
		
	}
	
	ReentrantLock buildLock, destroyLock;
	Condition notEmptyCondition, notFullCondition;
	AtomicInteger size;
	Node head,tail;
	int capacity;
	
	public BoundedEmpire(int capacity){
		//n i size of bounded queue
		result = BattleResult.Tie;
		battling = true;
		
		this.capacity = capacity;
		head = new Node();
		tail = head;
		size = new AtomicInteger(0);
		buildLock = new ReentrantLock();
		notFullCondition = buildLock.newCondition();
		destroyLock = new ReentrantLock();
		notEmptyCondition = destroyLock.newCondition();
	}
	
	public void build(){
		//Do something akin to enqueue
//		try {
//			Thread.sleep(20);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		
		buildLock.lock();
		try{
			if(size.get() == capacity){
				endBattling(BattleResult.HomeWin);
			} else {
				Node e = new Node();
				tail.next = tail = e;
				if(size.getAndIncrement() == 0){}
			}
		} finally {
			buildLock.unlock();
		}
		try {
			Thread.sleep(20);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void destroy(){
		//Do something akin to dequeue
//		try {
//			Thread.sleep(20);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		
		destroyLock.lock();
		try{
			if(size.get() == 0){
				endBattling(BattleResult.EnemyWin);
			} else {
				head = head.next;
				if(size.getAndDecrement() == capacity){}
			} 
			
		}finally {
			destroyLock.unlock();
		}
		try {
			Thread.sleep(20);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public boolean getBattling(){
		return battling;
	}
	
	public void endBattling(BattleResult result){
		battleLock.lock();
		if(battling){
			System.out.println("Ending Battle");
			battling = false;
			this.result = result;			
		}
		battleLock.unlock();

	}
	
	public void endBattling(){
		battleLock.lock();
		if(battling){
			System.out.println("Ending Battle");
			battling = false;
		}
		battleLock.unlock();
	}
	
	public BattleResult getResult(){
		//Used to tell state of the empire
		return result;
	}
}
