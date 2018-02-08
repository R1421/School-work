
public class SavingsAccountDriver {

	public static int numThreads = 3;
	public static Thread[] thread;
	public static SavingsAccount savings;
	
	public static void main(String[] args) {
		thread = new Thread[numThreads];
		savings = new SavingsAccount(0);
		int s;
		for(int i = 0; i < numThreads; i++){
			switch(i % 3){
				case 0: {
					thread[i] = new Thread(new Runnable(){
						public void run(){
							for(int i = 0; i < 100; i++){
								savings.deposit(100);
							}
						}
					});
					break;
				}
				case 1: {
					thread[i] = new Thread(new Runnable(){
						public void run(){
							for(int i = 0; i < 100; i++){
								savings.withdraw(10,false);
							}
						}
					});
					break;
				}
				case 2: {
					thread[i] = new Thread(new Runnable(){
						public void run(){
							for(int i = 0; i < 10; i++){
								savings.withdraw(100,true);
								try {
									Thread.sleep(100);
								} catch (InterruptedException e) {
									// TODO Auto-generated catch block
									e.printStackTrace();
								}
							}
						}
					});
					break;
				}
			}
		}
		System.out.println("Starting threads");
		for(int i = 0; i < numThreads; i++){
			thread[i].start();
		}
		
		for(int i = 0; i < numThreads; i++){
			try {
				thread[i].join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
