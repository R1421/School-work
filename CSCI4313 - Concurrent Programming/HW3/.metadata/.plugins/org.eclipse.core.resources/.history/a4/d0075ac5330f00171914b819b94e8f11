import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;

public class ConcurrentHashTableDriver {
	public static Queue<Double> add;
	public static Queue<Double> remove;
	public static ConcurrentHashTable list;
	
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
			if(i % 3 == 0 || i % 5 == 0){
				remove.add((double) i);
			}
		}
		
		list = new ConcurrentHashTable(100);
		for(int i = 0; i < numThreads; i++){
			if(i == 9){
				//Thread for deleting elements
				thread[i] = new Thread(new Runnable(){
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
				thread[i] = new Thread(new Runnable(){
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
			thread[i].start();
		}
//		for(int i = 0; i < numThreads; i++){
//			thread[i].start();
//		}
		for(int i = 0; i < numThreads; i++){
			try{
				thread[i].join();
			} catch (InterruptedException e){
				e.printStackTrace();
			}
		}
		
		//Give the list a moment to catch up
		try {
		    Thread.sleep(2000);
		} catch(InterruptedException ex) {
		    Thread.currentThread().interrupt();
		}
				
		for(int i = 0; i < 1000*numThreads; i++){
			if(i % 3 == 0 || i % 5 == 0){
				//Element could be in the list
				if(list.contains((double) i)){
					//System.out.println("Threads failed to delete " + i);
				}
			}
			else{
				//Element must be in the list
				if(!list.contains(i)){
					System.out.println("SYSTEM ERROR: " + i + " not in the list");
					//break;
				}
			}
//			System.out.println("Hash table returns " + list.contains(i) + " for item: " + i);
		}

	}
}
