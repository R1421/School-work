import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ConcurrentDoubleLinkedList {

	/*
	 * In implementing this concurrent data structure, one must only lock two nodes at a time when performing add or remove.
	 * This is because when a thread plans to alter the connections between two nodes, the validate function will always ensure
	 * that the proper nodes are being controlled by a thread before making any alterations. 
	 */
	public class Node{
		public Node pred;
		public Node succ;
		public double value;
		public boolean marked;
		private Lock lock;
		
		public Node(Double n){
			value = n;
			marked = false;
			lock = new ReentrantLock();
		}
		
		public void lock(){
			lock.lock();
		}
		
		public void unlock(){
			lock.unlock();
		}
	}
	
	private Node head;
	private Node tail;

	public ConcurrentDoubleLinkedList(){
		head = new Node(Double.NEGATIVE_INFINITY);
		tail = new Node(Double.POSITIVE_INFINITY);
		
		head.succ = tail;
		tail.pred = head;
	}
	
	private boolean validate(Node pred, Node curr){
		return !pred.marked && !curr.marked && pred.succ == curr && curr.pred == pred;
	}
	
	public boolean contains(double n){
		//Check to see whether a value is in the list
		Node curr = head;
		while(curr.value < n){
			curr = curr.succ;
		}
		return curr.value == n && !curr.marked;
	}
	
	public boolean add(double n){
		//Add a value to the list if it is not already there
		while(true){
			Node curr = head;
			Node pred;
			while(curr.value < n){
				curr = curr.succ;
			}
			pred = curr.pred;
			curr.lock();
			try{
				pred.lock();
				try{
					if(validate(pred,curr)){
						if(curr.value == n){
							return false;
						} else{
							Node node = new Node(n);
							node.pred = pred;
							node.succ = curr;
							curr.pred = node;
							pred.succ = node;
							return true;
						}
					}
				} finally{
					pred.unlock();
				}
			} finally{
				curr.unlock();
			}
		}
	}
	
	public boolean remove(double n){
		//Delete a value if it is in the list
		while(true){
			Node curr = head;
			Node pred;
			Node succ;
			while(curr.value < n){
				curr = curr.succ;
			}
			pred = curr.pred;
			succ = curr.succ;
			curr.lock();
			try{
					pred.lock();
					try{
						if(validate(pred,curr)){
							if(curr.value == n){
								//Value found, remove and return
								curr.marked = true;
								pred.succ = succ;
								succ.pred = pred;
								return true;
							} else{
								return false;
							}
						}
					} finally{
						pred.unlock();
					}
			} finally{
				curr.unlock();
			}
		}
	}
	
	public void printList(){
		
	}
}
