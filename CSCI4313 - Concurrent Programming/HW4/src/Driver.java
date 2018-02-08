
public class Driver {

	public static int numThreads = 16;
	public static Thread[] thread;
	public static Barrier barrier; 
	
	public static void foo(){
		System.out.println("foo");
		try {
			Thread.sleep(20);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public static void bar(){
		System.out.println("bar");
		try {
			Thread.sleep(20);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public static long runTest(){
		thread = new Thread[numThreads];
		barrier = new Barrier2(numThreads);
		for(int i = 0; i < numThreads; i++){
			thread[i] = new Thread(new Runnable(){
				public void run(){
					foo();
					barrier.runBarrier();
					bar();
				}
			});
		}
		
		
		long start = System.nanoTime();
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
		long time = System.nanoTime() - start;
		System.out.println(time);
		
		for(int i = 0; i < numThreads; i++){
			thread[i] = null;
		}
		barrier = null;
		return time;
	}
	
	public static void main(String[] args) {
		int numTests = 5;
		long[] times = new long[numTests];
		for(int i = 0; i < numTests; i++){
			times[i] = runTest();
		}
		long min = Long.MAX_VALUE;
		long max = 0;
		long total = 0;
		for(int i = 0; i < numTests; i++){
			if(times[i] > max){
				max = times[i];
			}
			if(times[i] < min){
				min = times[i];
			}
			System.out.println("Time: " + times[i]);
			total = total + times[i];
		}
		long adjustedAvg = (total - max - min)/(numTests-2);
		System.out.println("Adjusted average: " + adjustedAvg);
	}

}
