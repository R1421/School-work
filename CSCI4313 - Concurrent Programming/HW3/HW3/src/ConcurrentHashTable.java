
public class ConcurrentHashTable {

	/*
	 * This implementation is linearizable since the remove method always waits until the table contains the value to 
	 * be removed, before removing the value. This makes it possible to arrange the execution in such a way that the 
	 * removes always come after the adds.
	 */
	private ConcurrentDoubleLinkedList[] table;
	private int size;
	public ConcurrentHashTable(int size){
		this.size = size;
		table = new ConcurrentDoubleLinkedList[size];
		for(int i = 0; i < size; i++){
			table[i] = new ConcurrentDoubleLinkedList();
		}
	}
	
	private int hash(int n){
		return n % size;
	}
	
	public boolean contains(double n){
		return table[hash((int) n)].contains(n);
	}
	
	public boolean add(double n){
		return table[hash((int) n)].add(n);
	}
	
	public boolean remove(double n){
		while(!contains(n)){}
		return table[hash((int) n)].remove(n);
	}
}
