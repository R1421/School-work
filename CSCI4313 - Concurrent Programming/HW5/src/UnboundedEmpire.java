import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class UnboundedEmpire implements Empire {
	//Implements unbounded concurrent queue
	
	/*
	 * Code altered from Herlihy and Shavit - The art of multiprocessor programming; Chapter 10.5
	 */
	private BattleResult result;
	private boolean battling;
	private Lock battleLock = new ReentrantLock();
	
	public class Node{
		public AtomicReference<Node> next;
		
		public Node(){
			next = new AtomicReference<Node>(null);
		}
	}
	
	ReentrantLock buildLock, destroyLock;
	Condition notEmptyCondition, notFullCondition;
	AtomicInteger size, buildScore, destroyScore;
	AtomicReference<Node> head,tail;
	
	public UnboundedEmpire(){
		//n i size of bounded queue
		result = BattleResult.Tie;
		battling = true;
		
		Node n = new Node();
		head = new AtomicReference<Node>(n);
		tail = new AtomicReference<Node>(n);
		size = new AtomicInteger(40);
		buildScore = new AtomicInteger(0);
		destroyScore = new AtomicInteger(0);
		buildLock = new ReentrantLock();
		destroyLock = new ReentrantLock();
		for(int i = 0; i < 40; i++){
			Node newNode = new Node();
			Node last = tail.get();
			last.next.set(newNode);
			tail.set(newNode);
		}
	}

	public void build() {
		Node node = new Node();
		while(getBattling()) {
			Node last = tail.get();
			Node next = last.next.get();
			if(last == tail.get()){
				if(next == null){
					if(last.next.compareAndSet(next, node)){
						tail.compareAndSet(last,node);
						if(buildScore.addAndGet(5) >= 200){
							endBattling(BattleResult.HomeWin);
						}
						return;
					}
				}
			} else {
				tail.compareAndSet(last, next);
			}
			
		}
	}

	public void destroy() {
		while(getBattling()){
			Node first = head.get();
			Node last = tail.get();
			Node next = first.next.get();
			if(first == head.get()){
				if(first == last){
					if(next == null){
						//Empty
						return;
					}
					tail.compareAndSet(last, next);
				} else {
					if(head.compareAndSet(first, next)){
						if(destroyScore.addAndGet(5) >= 200){
							endBattling(BattleResult.EnemyWin);
						}
						return;
					}
				}
			}
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
