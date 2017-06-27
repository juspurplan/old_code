package your.WordScramble;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.res.AssetManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;

public class WordScrambleActivity extends Activity implements OnClickListener,OnTouchListener,OnItemSelectedListener
{
	private byte state; //0==menu, 1==game, 2 == endgame, 3=options, 4 == loading
	ArrayList<String> dictionary;
	ArrayList<String> searchlist;
	ArrayList<String> answers;
	ArrayList<LetterButton> buttons;
	boolean gamealive;
	int options_numletters; //
	int options_numletters_spinnerpos;
	Context thiscontext;
	public WordScrambleActivity()
	{
		dictionary = new ArrayList<String>();
		searchlist = new ArrayList<String>();
		answers = new ArrayList<String>();
		buttons = new ArrayList<LetterButton>();
	}

	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		thiscontext = this;
		SharedPreferences sp = getSharedPreferences("WordGame_prefs", 0);
		if( sp == null)
		{
			options_numletters=6;
			options_numletters_spinnerpos=0;
		}
		else
		{
			options_numletters = sp.getInt("numletters", 6);
			options_numletters_spinnerpos =sp.getInt("numletters_spinnerpos",0);
		}
		initMenu();
	}
	@Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		MenuInflater mi = getMenuInflater();
		mi.inflate(R.menu.game_menu, menu);
		return true;
	}
	@Override
	public boolean onPrepareOptionsMenu(Menu menu)
	{
		if(state == 0)
		{
			return false;
		}
		else if(state == 1)
		{
			if(menu.findItem(999) == null)
			{
				menu.add(Menu.NONE, 999, Menu.NONE, "End Game");
			}
			return true;
		}
		else if(state ==2)
		{
			if(menu.findItem(999) != null)
			{
				menu.removeItem(999);
			}
			return false;
		}
		else if(state == 3)
		{
			return false;
		}
		else
			return false;
	}
	@Override
	public boolean onOptionsItemSelected(MenuItem menuitem)
	{
		switch(menuitem.getItemId())
		{
		case R.id.restart:
			initGame();
			return true;
		case R.id.main_menu:
			saveGame(true);
			initMenu();
			return true;
		case 999:
			initEnd();
			return true;
		default:
			return super.onOptionsItemSelected(menuitem);
		}
	}

	@Override
	public void onClick(View v)
	{
		if(state ==0)
		{
			if(v.equals(findViewById(R.id.start)))
			{
				initGame();
			}
			else if(v.equals(findViewById(R.id.resume_button)))
			{
				resumeGame();
			}
			else if(v.equals(findViewById(R.id.options)))
			{
				initOptions();
			}
		}
		else if(state ==1)
		{
			if(((View)v.getParent()).equals(findViewById(R.id.include_game_buttons)))
			{
				LetterButton lb = (LetterButton)v;
				EditText et = (EditText)findViewById(R.id.text_field);
				if(!lb.isUsed())
				{
					et.setText(et.getText()+""+lb.getLetter());
					lb.setUsed(true);
				}
			}
			else if(v.equals(findViewById(R.id.backspace)))
			{
				EditText et = (EditText)findViewById(R.id.text_field);
				try
				{
					char lastletter = et.getText().toString().charAt(et.getText().toString().length()-1);
					et.setText( et.getText().toString().substring(0,et.getText().toString().length()-1) );
					LinearLayout ll = (LinearLayout) findViewById(R.id.include_game_buttons);
					for( View view: ll.getTouchables())
					{
						LetterButton lb = (LetterButton)view;
						if( lb.isUsed() && lb.getLetter() == lastletter)
						{
							lb.setUsed(false);
							lb.invalidate();
							break;
						}
					}
				}
				catch(StringIndexOutOfBoundsException e){}
			}
			else if(v.equals(findViewById(R.id.shuffle)))
			{
				Collections.shuffle(buttons);
				addButtons();
			}
			else if(v.equals(findViewById(R.id.enter)))
			{
				EditText et = (EditText)findViewById(R.id.text_field);
				TextView tv = (TextView)findViewById(R.id.used_words);
				String submit = et.getText().toString();
				for(int x =0; x<searchlist.size() ; x++)
				{
					String s = searchlist.get(x);
					if(submit.equalsIgnoreCase(s))
					{
						answers.add(s);
						searchlist.remove(s);
						String result = "["+searchlist.size()+"/"+(searchlist.size()+answers.size())+" Words Remaining]";
						for(int i = 0; i < answers.size(); i++)
						{
							result+=" "+answers.get(i);
						}
						tv.setText(result);
						for(int i = 0; i<s.length(); i++)
						{
							try
							{
								char lastletter = et.getText().toString().charAt(et.getText().toString().length()-1);
								et.setText( et.getText().toString().substring(0,et.getText().toString().length()-1) );
								LinearLayout ll = (LinearLayout) findViewById(R.id.include_game_buttons);
								for( View view: ll.getTouchables())
								{
									LetterButton lb = (LetterButton)view;
									if( lb.isUsed() && lb.getLetter() == lastletter)
									{
										lb.setUsed(false);
										lb.invalidate();
										break;
									}
								}
							}
							catch(StringIndexOutOfBoundsException e){}
						}
						break;
					}
				}
			}
		}
		else if(state == 2)
		{
			if(v.equals(findViewById(R.id.end_button)))
			{
				initMenu();
			}
		}
		else if(state == 3)
		{
			if(v.equals(findViewById(R.id.options_backbutton)))
			{
				initMenu();
			}
		}
	}
	public void onItemSelected(AdapterView<?> parent, View v, int pos, long id)
	{
		options_numletters_spinnerpos = pos;
		TextView numletters_text = (TextView)(findViewById(R.id.options_numletters_text));
		int selection = Integer.parseInt(parent.getItemAtPosition(pos).toString());
		options_numletters = selection;
		numletters_text.setText("Number of Letters\nCurrent: "+selection);
		numletters_text.invalidate();
	}
	public void onNothingSelected(AdapterView parent){}
	public boolean onTouch(View v, MotionEvent arg1)
	{
		// TODO Auto-generated method stu
		return false;
	}
	
	public void initMenu()
	{
		setContentView(R.layout.main);
		state = 0;
		findViewById(R.id.start).setOnClickListener(this);
		findViewById(R.id.options).setOnClickListener(this);
		try
		{
			InputStream is = openFileInput("WordGame_save");
			Scanner scan = new Scanner(is);
			if(scan.nextLine().equalsIgnoreCase("true"))
			{
				Button res = ((Button)findViewById(R.id.resume_button));
				LinearLayout ll = ((LinearLayout)findViewById(R.id.main_menu_buttons));
				if( !(ll.getChildAt(0).equals(res)) )
				{
					ll.addView(res,0);
				}
				res.setOnClickListener(this);
				res.setVisibility(Button.VISIBLE);
			}
			else
			{
				Button res = ((Button)findViewById(R.id.resume_button));
				LinearLayout ll = ((LinearLayout)findViewById(R.id.main_menu_buttons));
				if( ll.getChildAt(0).equals(res) )
				{
					ll.removeViewAt(0);
				}
			}
		}
		catch (FileNotFoundException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	public void initOptions()
	{
		state =3;
		setContentView(R.layout.options_menu);
		findViewById(R.id.options_backbutton).setOnClickListener(this);
		
		Spinner numletters_spinner = (Spinner)(findViewById(R.id.options_numletters_spinner));
		TextView numletters_text = (TextView)(findViewById(R.id.options_numletters_text));
		
		ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.options_numletters_array, android.R.layout.simple_spinner_item);
	    adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
	    numletters_spinner.setAdapter(adapter);
	    numletters_spinner.setOnItemSelectedListener(this);
	    
	    numletters_spinner.setSelection(options_numletters_spinnerpos);
	    numletters_text.setText("Number of Letters\nCurrent: "+options_numletters);
	}
	public void initEnd()
	{
		saveGame(false);
		state = 2;
		setContentView(R.layout.end_game);
		(findViewById(R.id.end_button)).setOnClickListener(this);
		TextView header = ((TextView)findViewById(R.id.end_header)); 
		TextView found = ((TextView)findViewById(R.id.end_answers)); 
		TextView unanswered = ((TextView)findViewById(R.id.end_unanswered)); 
		//header.setText(""); found.setText(""); unanswered.setText("");
		String temp = "Game Over: Letters[ ";
		for(LetterButton lb: buttons)
		{
			temp+=lb.getLetter()+" ";
		}
		temp+="]";
		header.setText(temp);
		temp="Found ["+answers.size()+"/"+(answers.size()+searchlist.size())+"] Words: ";
		for(String s : answers)
		{
			temp+=s+" ";
		}
		found.setText(temp);
		temp="Missed ["+searchlist.size()+"/"+(answers.size()+searchlist.size())+"] Words: ";
		for(String s : searchlist)
		{
			temp+=s+" ";
		}
		unanswered.setText(temp);
	}
	public void initGame()
	{
		state = 1;
		setContentView(R.layout.game);
		destroyGame();
		// temp game words
			/*searchlist.add("ABC");
			searchlist.add("A");
			searchlist.add("DBF");
			searchlist.add("ABCDEFG");
			searchlist.add("ABCDEFG");
			searchlist.add("ABCDEFG");
			searchlist.add("ABCDEFG");
			searchlist.add("ABCDEFG");
			searchlist.add("ABCDEFG");
			searchlist.add("ABCDEFG");
		////////
		// temp buttons
			for(int x=0; x<7 ;x++)
			{
				LetterButton b = new LetterButton(this, (char)('A'+x));
				b.setOnClickListener(this);
				buttons.add(b);
			}*/
		////////
		LoadDictTask task  = new LoadDictTask();
		task.execute(null);
		/*findViewById(R.id.backspace).setOnClickListener(this);
		findViewById(R.id.enter).setOnClickListener(this);
		findViewById(R.id.shuffle).setOnClickListener(this);
		for(int x= 0; x<buttons.size(); x++)
		{
			buttons.get(x).setOnClickListener(this);
		}
		addButtons();
		((TextView)findViewById(R.id.used_words)).setText("["+searchlist.size()+"/"+(searchlist.size()+answers.size())+" Words Remaining]");
		*/
	}
	public void addButtons()
	{
		LinearLayout v = (LinearLayout)findViewById(R.id.include_game_buttons);
		v.removeAllViewsInLayout();
		v.removeAllViews();
		for(LetterButton lb : buttons)
		{
			v.addView(lb);
		}
	}
	public void destroyGame()
	{
		buttons.clear();
		((EditText)findViewById(R.id.text_field)).setText("");
		((TextView)findViewById(R.id.used_words)).setText("");
		searchlist.clear();
		answers.clear();
	}
	public void saveGame(boolean check)
	{
		//saves game if true, if false, then does not save game
		SharedPreferences opt = getSharedPreferences("WordGame_prefs", 0);
		Editor edit = opt.edit();
		edit.putInt("numletters", options_numletters);
		edit.putInt("numletters_spinnerpos",options_numletters_spinnerpos);
		edit.commit();
		try
		{
			FileOutputStream os = openFileOutput("WordGame_save", Context.MODE_PRIVATE);
			PrintWriter pw = new PrintWriter(os);
			if(check)
			{
				pw.println("true");
				String temp = "";
				for(LetterButton lb : buttons)
				{
					temp+=lb.getLetter()+" ";
				}
				pw.println(temp);
				temp = "";
				for(String str : searchlist)
				{
					temp+=str+" ";
				}
				pw.println(temp);
				temp = "";
				for(String str : answers)
				{
					temp+=str+" ";
				}
				pw.println(temp);
			}
			else
			{
				pw.println("false");
			}
			pw.flush();
			pw.close();
			os.close();
		}
		catch (IOException e) {e.printStackTrace();}
	}
	public void resumeGame()
	{
		setContentView(R.layout.game);
		destroyGame();
		state = 1;
		findViewById(R.id.backspace).setOnClickListener(this);
		findViewById(R.id.enter).setOnClickListener(this);
		findViewById(R.id.shuffle).setOnClickListener(this);
		try
		{
			InputStream is = openFileInput("WordGame_save");
			Scanner scan = new Scanner(is);
			scan.nextLine();
			String letters = scan.nextLine();
			for(String s : letters.split(" "))
			{
				LetterButton lb = new LetterButton(this, s.charAt(0));
				lb.setOnClickListener(this);
				buttons.add(lb);
			}
			addButtons();
			String search = scan.nextLine();
			for(String s: search.split(" "))
			{
				if(!s.equals("") && !s.contains("\\s"))
					searchlist.add(s);
			}
			String ans = scan.nextLine();
			for(String s: ans.split(" "))
			{
				if(!s.equals("") && !s.contains("\\s"))
					answers.add(s);
			}
		}
		catch(IOException e) {e.printStackTrace();}
		String temp ="["+searchlist.size()+"/"+(searchlist.size()+answers.size())+" Words Remaining]";
		for(String word : answers)
		{
			temp+=" "+word;
		}
		((TextView)findViewById(R.id.used_words)).setText(temp);
	}
	public void genWord()
	{
	}
	public void onSaveInstanceState(Bundle state)
	{
		super.onSaveInstanceState(state);
	}
	public void onPause()
	{
		if(state==1)
			saveGame(true);
		super.onPause();
	}
	public void onStop() { super.onStop(); }
	public void onDestroy(){ super.onDestroy(); }
	
	//load dictionary AsyncTask
	class LoadDictTask extends AsyncTask<Void, Integer, Void>
	{
		protected void onPreExecute()
		{
			// TODO Auto-generated method stub
			super.onPreExecute();
			state =4;
			setContentView(R.layout.load);
		}
		protected Void doInBackground(Void... params)
		{
			// TODO Auto-generated method stub
			AssetManager am = getAssets();
			InputStream is=null;
			try
			{
				int file = (int)((Math.random()*2)+1);
				is = am.open(Integer.toString(options_numletters)+"."+file+".dat");
				InputStreamReader isr = new InputStreamReader(is);
				BufferedReader scan = new BufferedReader(isr);
				int size = Integer.parseInt(scan.readLine());
				long rand = (int)(Math.random()*size);
				for(int x =0; x< rand; x++)
				{
					scan.readLine();
				}
				String[] wordset = scan.readLine().split(" ");
				String baseword = wordset[0];
				for(int x =0; x<baseword.length(); x++)
				{
					buttons.add( new LetterButton(thiscontext, baseword.charAt(x)) );
				}
				for(int x=1; x<wordset.length; x++)
				{
					searchlist.add(wordset[x]);
				}
			}
			catch (IOException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return null;
		}
		protected void onPostExecute(Void result)
		{
			// TODO Auto-generated method stub
			super.onPostExecute(result);
			state = 1;
			setContentView(R.layout.game);
			((Activity) thiscontext).findViewById(R.id.backspace).setOnClickListener((OnClickListener) thiscontext);
			((Activity) thiscontext).findViewById(R.id.enter).setOnClickListener((OnClickListener) thiscontext);
			((Activity) thiscontext).findViewById(R.id.shuffle).setOnClickListener((OnClickListener) thiscontext);
			for(int x= 0; x<buttons.size(); x++)
			{
				buttons.get(x).setOnClickListener((OnClickListener) thiscontext);
			}
			Collections.shuffle(buttons);
			addButtons();
			((TextView)findViewById(R.id.used_words)).setText("["+searchlist.size()+"/"+(searchlist.size()+answers.size())+" Words Remaining]");
			
		}
		protected void onProgressUpdate(Integer... values)
		{
			// TODO Auto-generated method stub
			super.onProgressUpdate(values);
		}
	}
}