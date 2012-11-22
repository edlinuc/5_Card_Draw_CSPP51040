import java.util.List;
import java.util.LinkedList;

public class LL{
    public static void main(String[] args){
	List<String> list = new LinkedList<String>();
	list.add("John");
	list.add("Grant");
	list.add("Kyle");
	list.add("Dave");
	list.add("Ron");
	System.out.println(list);
	list.remove("Ron");
	System.out.println(list);
	list.add(0,"Ron");
	System.out.println(list);
	list.add(4,"Ron");
	System.out.println(list);
	list.add("Ron");
	list.add("Ron");
	list.add("Ron");
	list.add("Ron");
	list.add("Ron");
	list.add("Ron");
    }


}