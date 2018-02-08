/*This is the code for problem 1 of HW1
Implemented by Raymond Duncan
*/
public class HW1 {
	private static int count = 0;

	public static void main(String[] args){
		int numThreads = 128;
		
		//Create an array of threads that will be used to start all threads and wait for all threads to finish
		Thread[] threads = new Thread[numThreads];
		
		//Initialize and start the threads
		for (int i = 0; i < numThreads; i++){
			threads[i] = new Thread(new Runnable(){
				//Anonymous class (Taken from lecture slides) which adds 100 to count from each thread
				public void run(){
					for (int i = 0; i < 100; i++){
						count++;
					}
				}
			});
			threads[i].start();
		}
		
		//Wait for threads to finish
		for (int i = 0; i < numThreads; i++){
			//Use try catch for exception handling
			try{
				threads[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		System.out.println(count);
	}
	
}

