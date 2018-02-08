
public interface Empire {

	public void build();
	public void destroy();
	public boolean getBattling();
	public void endBattling(BattleResult result);
	public void endBattling();
	public BattleResult getResult();
	
}
