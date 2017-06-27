import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Set;


public class Assembler
{
	private final static String[] COMP_INSTRUCTION = 	{"0",		"1",		"-1",		"D",	  "A",      "!D",       "!A",     "-D",      "-A",      "D+1",     "A+1",     "D-1",     "A-1",     "D+A",     "D-A",     "A-D",     "D&A",     "D|A",     "M",       "!M",      "-M",      "M+1",     "M-1",     "D+M",     "D-M",     "M-D",     "D&M",     "D|M"};
	private final static String[] COMP_MACHINE = 		{"0101010", "0111111", "0111010", "0001100", "0110000", "0001101", "0110001", "0001111", "0110011", "0011111", "0110111", "0001110", "0110010", "0000010", "0010011", "0000111", "0000000", "0010101", "1110000", "1110001", "1110011", "1110111", "1110010", "1000010", "1010011", "1000111", "1000000", "1010101"};
	private final static String[] JUMP_INSTRUCTION = {};
	static HashMap<String,Integer> symbols;
	static HashMap<String, Integer> labels;
	static ArrayList<Integer> used_addresses;
	
	public Assembler()
	{
		symbols = new HashMap<String,Integer>();
		labels = new HashMap<String,Integer>();
		used_addresses = new ArrayList<Integer>();
	}
	
	
	public static void main(String[]arg)
	{
		if(arg.length>0)
		{
			String path = arg[0];
			assemble(path);
		}
		else
		{
			System.out.println("No params..");
		}
	}
	public static void assemble(String path /*,String dest*/)
	{
		if( !(validate(path)) )
			return;
		
		//prelim address check, see what addresses are used
		Scanner scan = new Scanner(path);
		while(scan.hasNext())
		{
			String instruction = scan.nextLine();
			instruction = instruction.replaceAll("[\\s&&[^\\n]]", "");
			instruction = removeComments(instruction);
			if(instruction.charAt(0) == '@')
			{
				try
				{
					int a = Integer.parseInt(instruction.substring(1));
					used_addresses.add(a);
				}
				catch(NumberFormatException e){}
			}
		}
		
		//first pass
		int line=0;
		int rom=0;
		scan = new Scanner(path);
		while(scan.hasNext())
		{
			String instruction = scan.nextLine();
			instruction = instruction.replaceAll("[\\s&&[^\\n]]", "");
			instruction = removeComments(instruction);
			
			int type = typeCheck(instruction);
			if(type == 0 )
			{
				String label = instruction.substring(1, instruction.length()-1);
				labels.put(label, rom);
			}
			if(type == 1)
			{
				String a = instruction.substring(1);
				try
				{
					int address= Integer.parseInt(a);
					used_addresses.add(address);
				}
				catch(NumberFormatException e)
				{
					int rand = (int)(Math.random()*32768);
					while ( used_addresses.contains(rand) )
					{
						rand = (int)(Math.random()*32768);
					}
					used_addresses.add(rand);
					symbols.put(a, rand);
				}
			}
			
			if(type == 1 || type == 2)
				rom++;
			if(type == 3)
			{
				System.out.println("Error at line: "+line+"\nExiting");
				System.exit(1);
			}
			line++;
		}
		
		//second pass
		line=0;
		rom=0;
		scan = new Scanner(path);
		while(scan.hasNext())
		{
			String instruction = scan.nextLine();
			/*print*/System.out.print(instruction+" >> ");
			instruction = instruction.replaceAll("[\\s&&[^\\n]]", "");
			instruction = removeComments(instruction);
			
			int type = typeCheck(instruction);
			String result;
			switch(type)
			{
			case 0:
				break;
			case 1:
				result = genMachineCode(instruction, type);
				break;
			case 2:
				result = genMachineCode(instruction, type);
				break;
			case 3:
				System.out.println("Error at line: "+line);
				System.exit(1);
			}
			
			if(type == 1 || type == 2)
				rom++;
			line++;
		}
	}
	public static String genMachineCode(String instruction, int type)
	{
		if(type == 1)
		{
			String result = "";
			String a = instruction.substring(1);
			if(labels.containsKey(a))
			{
				int address = labels.get(a);
				result = "0"+to15BitAddress(address);
				return result;
			}
		}
		else
		{
			int equal = instruction.indexOf('=');
			int semi = instruction.indexOf(';');
			String dest = instruction.substring(0, equal);
			String comp = "";
			String jump="";
			if(semi == -1)
			{
				comp = instruction.substring(equal+1);
			}
			else
			{
				comp = instruction.substring(equal+1, semi);
				jump = instruction.substring(semi+1);
			}
			
			//comp
			String result = "111";
			int index =0;
			for(int x = 0; x< COMP_INSTRUCTION.length; x++)
			{
				if(comp.equalsIgnoreCase(COMP_INSTRUCTION[x]))
				{
					index = x;
					break;
				}
			}
			result += COMP_MACHINE[index];
			
			//dest
			dest = dest.replaceAll(",", "");
			boolean D=false,A=false,M = false;
			for(int x=0; x<dest.length(); x++)
			{
				char c = dest.charAt(x);
				if(c == 'D')
					D = true;
				else if(c == 'A')
					A = true;
				else if (c=='M')
					M = true;
				else
					result += "ERROR";
			}
			if(A)
				result +="1";
			else
				result +="0";
			if(D)
				result +="1";
			else
				result +="0";
			if(M)
				result +="1";
			else
				result +="0";
			
			//jump
			
		}
	}
	public static String to15BitAddress(int address)
	{
		String a = Integer.toBinaryString(address);
		if(a.length()>15)
		{
			return a.substring(a.length()-15);
		}
		while(a.length()<15)
		{
			a = "0"+a;
		}
		return a;
	}
	public static int typeCheck(String instruction)
	{
		//0 = label
		//1 = A instruction
		//2 = C instruction
		//3 = error
		
		int leftbracket = instruction.indexOf("{");
		int rightbracket = instruction.indexOf("}");
		if( leftbracket==0 && rightbracket==instruction.length()-1 )
		{
			return 0;
		}
		int at = instruction.indexOf("@");
		if(at == 0)
		{
			return 1;
		}
		int equal = instruction.indexOf("=");
		int semi = instruction.indexOf(";");
		if(equal == -1 )
		{
			return 3;
		}
		String dest = instruction.substring(0,equal);
		dest = dest.replaceAll(",", "");
		for(int x= 0 ; x<dest.length(); x++)
		{
			if( dest.charAt(x) != 'A' || dest.charAt(x) != 'D' || dest.charAt(x) != 'M' )
			{
				return 3;
			}
		}
		String comp = "";
		if(semi == -1)
		{
			comp = instruction.substring(equal +1);
		}
		else
		{
			comp = instruction.substring(equal+1, semi);
		}
		boolean contains = false;
		for(int x=0; x<COMP_INSTRUCTION.length; x++)
		{
			if(comp.equals(COMP_INSTRUCTION[x]))
			{
				contains = true;
				break;
			}
		}
		if(!contains)
		{
			return 3;
		}
		if(semi != -1)
		{
			String jump = instruction.substring(semi=1);
			contains = false;
			for(int x=0; x<JUMP_INSTRUCTION.length; x++)
			{
				if(jump.equals(JUMP_INSTRUCTION[x]))
				{
					contains = true;
					break;
				}
			}
			if(!contains)
			{
				return 3;
			}
		}
		return 2;
	}
	public static String removeComments(String instruction)
	{
		String result = instruction;
		int index = result.indexOf("//");
		if(index == -1)
		{
			return result;
		}
		else
		{
			result = result.replace( result.substring(index), "" );
			return result;
		}
	}
	public static boolean validate(String path)
	{
		if((path.substring(path.length()-4, path.length())).equalsIgnoreCase(".asm") )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}