
public class FilterLockDriver {

	public static long test(int numThreads) {
		// TODO Auto-generated method stub
		
		Thread[] threads = new Thread[numThreads];
		FilterLock fl = new FilterLock(numThreads);
		long start = System.nanoTime();
		for(int i = 0; i < numThreads; i++){
			threads[i] = new Thread(new Runnable(){
				int id = (int) (Thread.currentThread().getId()) % numThreads;
				public void run(){
					for(int x = 0; x < 100; x++){
						fl.lock();
						fl.incrementResource();
						fl.unlock();
					}
				}
			});
			threads[i].start();
		}
		for(int i = 0; i < numThreads; i++){
			try{
				threads[i].join();
			} catch (InterruptedException e){
				e.printStackTrace();
			}
		}
		//System.out.println(fl.getResource());
		return System.nanoTime() - start;

	}

	public static void main(String[] args){
		System.out.println("Running FilterLockDriver");
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
