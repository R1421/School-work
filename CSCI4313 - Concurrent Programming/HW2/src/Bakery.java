
public class Bakery {
	private int resource;
	private boolean[] flags;
	private int[] labels;
	private int numThreads;
	private int max;
	
	public Bakery(int n){
		resource = 0;
		flags = new boolean[n];
		labels = new int[n];
		numThreads = n;
		for(int i = 0; i < n; i++){
			flags[i] = false;
			labels[i] = 0;
		}
		max = 0;
	}
	public void lock(){
		int i = (int) (Thread.currentThread().getId()) % numThreads;
		flags[i] = true;
		labels[i] = max++; //Provides the same effect as max(labels[x] + 1) with less overhead;
		boolean acquire = false;
		while(!acquire){
			acquire = true;	//If conditions met, exit
			for(int x = 0; x < numThreads; x++){
				if(x != i && flags[x] && (labels[x] < labels[i] || (labels[x] == labels[i] && x < i))) {
					//Acquisition conditions not met
					acquire = false;
					break;
				}
			}
		}
	}
	public void unlock(){
		int i = (int) (Thread.currentThread().getId()) % numThreads;
		flags[i] = false;
	}
	public int getResource(){
		return resource;
	}
	public void incrementResource(){
		resource++;
	}
}
