import java.util.*;

public class TreeLockDriver {

	public static long test(int numThreads) throws Exception {
		// TODO Auto-generated method stub
//		TreeLock tl = new TreeLock(16, 0);
//		System.out.println(tl);
//		tl.printLeaves();

		TreeLock b = new TreeLock(numThreads, 0);
		Thread[] threads = new Thread[numThreads];
		long start = System.nanoTime();
		for(int i = 0; i < numThreads; i++){
			threads[i] = new Thread(new Runnable(){
				public void run(){

					for(int x = 0; x < 100; x++){
						b.lock();
						b.incrementResource();
						b.unlock();
					}
				}
			});
			//System.out.println(threads[i].getId() % numThreads);
			threads[i].start();
		}
		for(int i = 0; i < numThreads; i++){
			try{
				threads[i].join();
			} catch (InterruptedException e){
				e.printStackTrace();
			}
		}
		//System.out.println(b.getResource());
		return System.nanoTime() - start;
	}

	public static void main(String[] args){
		System.out.println("Running TreeLockDriver");
		int tests = 10;
		long totalTime = 0;
		for(int i = 0; i < tests; i++){
			try {
				totalTime += test(8);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		System.out.println("\tAverage time for 8 threads: " + totalTime/tests + " nanoseconds");
		
		
		totalTime = 0;
		for(int i = 0; i < tests; i++){
			try {
				totalTime += test(64);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		System.out.println("\tAverage time for 64 threads: " + totalTime/tests + " nanoseconds");
	}
}
