import java.util.*;
import java.util.concurrent.TimeUnit;

public class LinkedListDriver {

	public static Queue<Double> add;
	public static Queue<Double> remove;
	public static ConcurrentSingleLinkedList list;
	
	synchronized public static double popAddQueue(){
			try{
				return add.remove();
			} catch (NoSuchElementException e){
				return Double.POSITIVE_INFINITY;
			}
		}
	
	synchronized public static double popRemoveQueue(){
		try{
			return remove.remove();
		} catch (NoSuchElementException e){
			return Double.POSITIVE_INFINITY;
		}
	}
	
	public static void main(String[] args) {
		int numThreads = 100;
		Thread[] thread = new Thread[numThreads];
		
		add = new LinkedList<Double>();
		remove = new LinkedList<Double>();
		for(int i = 0; i < 1000*numThreads; i++){
			add.add((double) i);
			if(i % 3 == 0 || i % 5 == 0 || i % 8 == 0){
				remove.add((double) i);
			}
		}
		
		list = new ConcurrentSingleLinkedList();
		for(int i = 1; i < numThreads + 1; i++){
			if(i % 5 == 0){
				//Thread for deleting elements
				thread[i-1] = new Thread(new Runnable(){
					public void run(){
						double i;
						boolean success;
						while(true){
							i = popRemoveQueue();
							if(i == Double.POSITIVE_INFINITY){
								break;
							}
							success = list.remove(i);
//							if(!success){
//								System.out.println("Failed to remove " + i);
//							}
						}
					}
				});
			} else{
				//Thread or adding elements
				thread[i-1] = new Thread(new Runnable(){
					public void run(){
						double i;
						boolean success;
						while(true){
							i = popAddQueue();
							if(i == Double.POSITIVE_INFINITY){
								break;
							}
							success = list.add(i);
//							if(!success){
//								System.out.println("Failed to add " + i);
//							}
						}
					}
				});
			}
		}
		for(int i = 0; i < numThreads; i++){
			thread[i].start();
		}
		for(int i = 0; i < numThreads; i++){
			try{
				thread[i].join();
			} catch (InterruptedException e){
				e.printStackTrace();
			}
		}
		
		//Give the list a moment to catch up
		try {
		    Thread.sleep(1000);
		} catch(InterruptedException ex) {
		    Thread.currentThread().interrupt();
		}
		
		//Check for errors
		for(int i = 0; i < 1000*numThreads; i++){
			if(i % 3 == 0 || i % 5 == 0 || i % 8 == 0){
				//Element could be in the list
				if(list.contains((double) i)){
//					System.out.println("Threads failed to delete " + i);
				}
			}
			else{
				//Element must be in the list
				if(!list.contains(i)){
					System.out.println("SYSTEM ERROR: " + i + " not in the list");
					//break;
				}
			}
		}

	}

}
