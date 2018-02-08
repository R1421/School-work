
public class FilterLock {	
	private volatile int[] levels;
	private int numLevels;
	private volatile int[] victims;
	private int resource;
	
	public FilterLock(int n){
		levels = new int[n];
		for(int i = 0; i < numLevels; i++){
			levels[i] = 0;
		}
		numLevels = n;
		victims = new int[n];
		resource = 0;
	}

	public void lock(){
		int id = (int)(Thread.currentThread().getId()) % numLevels;
		//System.out.println(id);
		for(int i = 1; i < numLevels; i++){
			levels[id] = i;
			victims[i] = id;
			boolean acquire = false;
			while(!acquire){
				acquire = true;
				for(int j = 0; j < numLevels; j++){
					if(j != id && levels[j] >= i && victims[i] == id) {
						acquire = false;
						break;
					}
				}
			}
		}
	}
	public void unlock(){
		int id = (int)(Thread.currentThread().getId()) % numLevels;
		levels[id] = 0;
	}
	public int getResource(){
		return resource;
	}
	public void incrementResource(){
		resource++;
	}
}
