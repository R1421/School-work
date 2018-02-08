import java.util.Random;

public class Observer {
	//Watches the game and prints winner
	private static int RANDOM_WAIT = 50;
	
	public static void main(String[] args){
		//Run Tests
		System.out.println("Starting game: n1=64, n2=32");
		observe(64,32);
		System.out.println("Starting game: n1=32, n2=32");
		observe(32,32);
		System.out.println("Starting game: n1=32, n2=64");
		observe(32,64);
//		observe(8,4);
	}
	
	public static void observe(int n1, int n2){
		int numThreads = n1 + n2;
		Thread[] thread = new Thread[numThreads];
//		Empire empire = new BoundedEmpire(20);
		Empire empire = new UnboundedEmpire();
		Random random = new Random();
		
		for(int i = 0; i < numThreads; i++){
			if(i < n1){
				//Home Team
				thread[i] = new Thread(new Runnable(){
					public void run(){
						try {
							Thread.sleep(random.nextInt(RANDOM_WAIT));
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						while(empire.getBattling()){
							empire.build();
						}
					}
				});
			} else {
				//Enemy Team
				thread[i] = new Thread(new Runnable(){
					public void run(){
//						try {
//							Thread.sleep(random.nextInt(RANDOM_WAIT));
//						} catch (InterruptedException e) {
//							// TODO Auto-generated catch block
//							e.printStackTrace();
//						}
						while(empire.getBattling()){
							empire.destroy();
						}
					}
				});
			}
		}
		
		//Start game
		long start = System.currentTimeMillis();
		for(int i = 0; i < numThreads; i++){
			thread[i].start();
		}
		
		while(System.currentTimeMillis()-start < 5000 && empire.getBattling()){}
		empire.endBattling();
		
		for(int i = 0; i < numThreads; i++){
			try {
				thread[i].join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		BattleResult result = empire.getResult();
		switch(result){
		case HomeWin:
			System.out.println("\tHOME TEAM WINS");
			break;
		case Tie:
			System.out.println("\tTIE");
			break;
		case EnemyWin:
			System.out.println("\tENEMY TEAM WINS");
			break;
		}
	}
}
