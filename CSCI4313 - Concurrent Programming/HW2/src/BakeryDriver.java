
public class BakeryDriver {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int numThreads = 64;
		Bakery b = new Bakery(numThreads);
		Thread[] threads = new Thread[numThreads];
		for(int i = 0; i < numThreads; i++){
			threads[i] = new Thread(new Runnable(){
				public void run(){
					for(int i = 0; i < 100; i++){
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
		System.out.println(b.getResource());
	}

}
