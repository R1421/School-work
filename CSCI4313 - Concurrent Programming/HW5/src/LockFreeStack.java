import java.util.EmptyStackException;
import java.util.concurrent.atomic.AtomicReference;

public class LockFreeStack {
	/*
	 * Adapted from  Herlihy and Shavit - The Art of Multiprocessor Programming; Chapter 11.2
	 */
	private class Node{
		public int value;
		public int grade;
		private AtomicReference<Node> next;
		
		public Node(int value, int grade){
			this.value = value;
			this.grade = grade;
			next = new AtomicReference<Node>(null);
		}
	}
	AtomicReference<Node> top = new AtomicReference<Node>(null);
	static final int MIN_DELAY = 50;
	static final int MAX_DELAY = 100;
	Backoff backoff = new Backoff(MIN_DELAY,MAX_DELAY);
	
	
	protected boolean tryPush(Node node){
		Node oldTop = top.get();
		node.next.set(oldTop);
		return(top.compareAndSet(oldTop, node));
	}
	
	public void push(int value, int grade){
		Node node = new Node(value, grade);
		while(true){
			if(tryPush(node)){
				return;
			} else {
				try {
					backoff.backoff();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}
	
	protected Node tryPop(int grade) throws EmptyStackException {
		Node oldTop = top.get();
		if(oldTop == null){
			throw new EmptyStackException();
		}
		Node newTop = oldTop.next.get();
		if(oldTop.grade == grade && top.compareAndSet(oldTop, newTop)){
			return oldTop;
		} else {
			return null;
		}
	}
	
	public int pop(int grade) throws EmptyStackException {
		while(true){
			Node returnNode = tryPop(grade);
			if(returnNode != null){
				return returnNode.value;
			} else {
				try {
					backoff.backoff();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}
}
