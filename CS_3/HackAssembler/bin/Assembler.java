import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Set;


public class Assembler
{
	private final static String[] COMP_INSTRUCTION = 	{"0",		"1",		"-1",		"D",	  "A",      "!D",       "!A",     "-D",      "-A",      "D+1",     "A+1",     "D-1",     "A-1",     "D+A",     "D-A",     "A-D",     "D&A",     "D|A",     "M",       "!M",      "-M",      "M+1",     "M-1",     "D+M",     "D-M",     "M-D",     "D&M",     "D|M"};
	private final static String[] COMP_MACHINE = 		{"0101010", "0111111", "0111010", "0001100", "0110000", "0001101", "0110001", "0001111", "0110011", "0011111", "0110111", "0001110", "0110010", "0000010", "0010011", "0000111", "0000000", "0010101", "1110000", "1110001", "1110011", "1110111", "1110010", "1000010", "1010011", "1000111", "1000000", "1010101"};
	private final static String[] JUMP_INSTRUCTION = {"JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", "JMP"};
	private final static String[] JUMP_MACHINE = 	 {"001", "010", "011", "100", "101", "110", "111", ""};
	static HashMap<String,Integer> symbols;
	static HashMap<String, Integer> labels;
	static ArrayList<Integer> used_addresses;
	
	public Assembler()
	{
		
	}
	
	
	public static void main(String[]arg) throws FileNotFoundException
	{
		symbols = new HashMap<String,Integer>();
		labels = new HashMap<String,Integer>();
		used_addresses = new ArrayList<Integer>();
		
		String source_path ="";
		String result_path ="";
		try
		{
			if(arg.length==2)
			{
				source_path = arg[0].replaceAll("\"", "");
				result_path = arg[1].replaceAll("\"", "");;
				assemble(source_path, result_path);
			}
			else if(arg.length==1)
			{
				source_path = arg[0].replaceAll("\"", "");;
				result_path = source_path.substring(0, source_path.length()-3) + "hack";
				assemble(source_path, result_path);
			}
			else if(arg.length==0)
			{
				System.out.println("\nUsage: assemble \"SOURCE\" [\"DEST\"]\n\tNo Args:\tDisplays this Message\n\t\"SOURCE\":\tPath pointing to the file to be assembled\n\t\"DEST\":\tPath pointing to the destination file. If parameter left blank, filename will default to \"SOURCEFILE.hack\" in the local directory of the source file\n");
			}
			else
			{
				System.out.println("\nError: Too Many Params\n");
			}
		}catch(FileNotFoundException e)
		{
			System.out.println("\nError: File Not Found\n");
		}
		
	}
	public static void assemble(String path ,String dest) throws FileNotFoundException
	{
		if( !(validate(path)) )
		{
			System.out.println("Bad Path");
			return;
		}
		System.out.println("\nAssembling \""+path+"\" into \""+dest+"\"");
		System.out.println("\nPrelim Check...");
		//prelim address check, see what addresses are used
		Scanner scan = new Scanner(new File(path));
		int l =0; 
		while(scan.hasNext())
		{
			String instruction = scan.nextLine();
			instruction = instruction.replaceAll("[\\s&&[^\\n]]", "");
			instruction = removeComments(instruction);
			System.out.println(l+":"+instruction);
			if(!instruction.equals("") && instruction.charAt(0) == '@' )
			{
				try
				{
					int a = Integer.parseInt(instruction.substring(1));
					used_addresses.add(a);
				}
				catch(NumberFormatException e){}
			}
			l++;
		}
		
		System.out.println("\nFirst pass...");
		//first pass
		int line=0;
		int rom=0;
		scan = new Scanner(new File(path));
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
		
		System.out.println("Table:");
		System.out.println("Symbols:"+symbols);
		System.out.println("Labels:"+labels);
		System.out.println("Used Addresses:"+used_addresses);
		
		System.out.println("\nSecond pass...");
		//second pass
		line=0;
		rom=0;
		scan = new Scanner(new File(path));
		PrintWriter pw = new PrintWriter(new File(dest));
		while(scan.hasNext())
		{
			String instruction = scan.nextLine();
			instruction = instruction.replaceAll("[\\s&&[^\\n]]", "");
			instruction = removeComments(instruction);
			/*print*/System.out.print(line+":"+instruction+" >> ");
			
			int type = typeCheck(instruction);
			
			String result="No Machine Code Generated";
			switch(type)
			{
			case 0:
				break;
			case 1:
				result = genMachineCode(instruction, type);
				pw.println(result);
				break;
			case 2:
				result = genMachineCode(instruction, type);
				pw.println(result);
				break;
			case 3:
				System.out.println("Error at line: "+line);
				System.exit(1);
			}
			
			System.out.print(result+"\n");
			
			if(type == 1 || type == 2)
				rom++;
			line++;
		}
		pw.flush();
		pw.close();
		System.out.println("\nDone...\n");
	}
	public static String genMachineCode(String instruction, int type)
	{
		String result = "";
		if(type == 1)
		{
			String a = instruction.substring(1);
			if(labels.containsKey(a))
			{
				int address = labels.get(a);
				result = "0"+to15BitAddress(address);
				return result;
			}
			else if(symbols.containsKey(a))
			{
				int address = symbols.get(a);
				result = "0"+to15BitAddress(address);
				return result;
			}
			else
			{
				result = "0"+to15BitAddress(Integer.parseInt(a));
				return result;
			}
		}
		else
		{
			int equal = instruction.indexOf('=');
			int semi = instruction.indexOf(';');
			String dest = "";
			String comp = "";
			String jump="";
			if(equal != -1)
			{
				dest = instruction.substring(0, equal);
			}
			if(semi == -1 && equal != -1)
			{
				comp = instruction.substring(equal+1);
			}
			else
			{
				comp = instruction.substring(equal+1, semi);
				jump = instruction.substring(semi+1);
			}
			
			//comp
			result = "111";
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
					result += "_ERROR_";
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
			if(semi == -1)
			{
				result += "000";
			}
			else
			{
				index = 0;
				for(int x=0; x<JUMP_INSTRUCTION.length; x++)
				{
					if(jump.equalsIgnoreCase(JUMP_INSTRUCTION[x]))
					{
						index = x;
						break;
					}
				}
				result += JUMP_MACHINE[index];
			}
			return result;
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
		//4 = empty line
		if(instruction.equals(""))
		{
			return 4;
		}
		
		int leftbracket = instruction.indexOf("(");
		int rightbracket = instruction.indexOf(")");
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
		/*if(equal == -1 )
		{
			return 3;
		}*/
		if(equal != -1)
		{
			String dest = instruction.substring(0,equal);
			dest = dest.replaceAll("[,\\s]", "");
			for(int x= 0 ; x<dest.length(); x++)
			{
				if( dest.charAt(x) != 'A' || dest.charAt(x) != 'D' || dest.charAt(x) != 'M' )
				{
					//return 3;
				}
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
				//return 3;
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
	public static boolean validate(String path) throws FileNotFoundException
	{
		Scanner scan = new Scanner(new File(path));
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