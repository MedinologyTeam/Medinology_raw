/*
 medinology Android 1.0
 */
package com.kyunggi.medinology;

import android.app.*;
import android.content.*;
import android.os.*;
import android.view.*;
import android.view.View.*;
import android.widget.*;
import java.io.*;
import java.util.*;
import java.nio.*;


public class MainActivity extends Activity implements OnClickListener, CheckBox.OnCheckedChangeListener
{
	//남자가 임신 체크 하는 것을 막기 위해서
	@Override
	public void onCheckedChanged(CompoundButton p1, boolean p2)
	{
		if (p1 instanceof CheckBox && p1 == CB_Preg)
		{
			if (p2 == true)
			{
				RB_Male.setChecked(false);
				RB_Female.setChecked(true);
				RG_Gender.setEnabled(false);
			}
			else
			{
				RG_Gender.setEnabled(true);
			}
		}
		else if (p1 instanceof RadioButton && p1 == RB_Male)
		{
			if (p2 == true)
			{
				CB_Preg.setChecked(false);
				CB_Preg.setEnabled(false);
			}
			else
			{
				CB_Preg.setEnabled(true);
			}
		}
	}
	//XML 파일 오류등으로 직접 생성할 컴포넌트들
	LinearLayout mainLayout;
	FrameLayout firstFrame;
	ScrollView scrollView;
	LinearLayout inlinearLayout;
	ArrayList<FrameLayout> symptomTabFrames;
	Button BT_gosym;
	Button BT_getResult;
	ArrayList<Button> nextButtons=null;
	ArrayList<Button> backButtons=null;
	CheckBox CB_Preg;
	NumberPicker NP_Age;
	RadioGroup RG_Gender;
	RadioButton RB_Male,RB_Female;
	//native 메소드에 넘겨줄 변수들
	boolean male;
	boolean preg;
	int age;
	ArrayList<Byte> symptombytes=new ArrayList<Byte>();		//원래는 boolean 배열이었으나 호환성을 위해 byte로
	//버튼이 클릭되었을 때 호출됨
	@Override
	public void onClick(View p)
	{
		Button p1=(Button)p;
		if (nextButtons == null)return;
		int sz=nextButtons.size();
		for (int i=0;i < sz;++i)
		{
			Button button=nextButtons.get(i);
			if (button == p1)
			{
				if (i == sz - 1)
				{
					Invoke();
				}
				else
				{
					if (i != 0)
					{
						symptomTabFrames.get(i - 1).setVisibility(View.GONE);
						//TODO:체크박스들의 값 얻어오기
						for (int j = 0; j < symptomTabFrames.get(i - 1).getChildCount(); j++)
						{
							View v = symptomTabFrames.get(i - 1).getChildAt(j);
							if (v instanceof CheckBox)
							{
								symptombytes.add(new Byte((byte)(((CheckBox)v).isChecked() ?1: 0)));
							}
						}
					}
					else
					{
						age = NP_Age.getValue();
						preg = CB_Preg.isChecked();
						male = RB_Male.isChecked();
						firstFrame.setVisibility(View.GONE);
					}
					symptomTabFrames.get(i).setVisibility(View.VISIBLE);
				}
				mainLayout.invalidate();
			}
		}	
	}
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {

        super.onCreate(savedInstanceState);
		try
		{
			mainLayout = new LinearLayout(this);
			firstFrame = new FrameLayout(this);
			scrollView = new ScrollView(this);
			inlinearLayout = new LinearLayout(this);
			TextView tvtitle=new TextView(this);
			RG_Gender = new RadioGroup(this);
			RB_Male = new RadioButton(this);
			RB_Female = new RadioButton(this);
			CB_Preg = new CheckBox(this);
			TextView tvage=new TextView(this);
			NP_Age = new NumberPicker(this);
			BT_gosym = new Button(this);
			LinearLayout.LayoutParams p = new LinearLayout.LayoutParams(
				LinearLayout.LayoutParams.MATCH_PARENT,
				LinearLayout.LayoutParams.WRAP_CONTENT
			);
			tvtitle.setText("Medinology - 기초 정보");
			tvtitle.setTextSize(60);
			inlinearLayout.setOrientation(LinearLayout.VERTICAL);
			RG_Gender.setOrientation(RG_Gender.HORIZONTAL);
			RB_Female.setText("여자");
			RB_Male.setText("남자");
			RB_Male.setChecked(false);
			RB_Female.setChecked(false);
			RG_Gender.addView(RB_Male);
			RG_Gender.addView(RB_Female);
			CB_Preg.setText("임신함");
			CB_Preg.setChecked(false);
			CB_Preg.setOnCheckedChangeListener(this);
			RB_Male.setOnCheckedChangeListener(this);
			tvage.setText("나이");
			tvage.setTextSize(30);
			BT_gosym.setText("증상 고르러 가기");
			BT_gosym.setTextSize(40);
			BT_gosym.setOnClickListener(this);
			NP_Age.setMinValue(0);
			NP_Age.setMaxValue(250);
			NP_Age.setWrapSelectorWheel(false);
			NP_Age.setOnLongPressUpdateInterval(100);
			inlinearLayout.addView(tvtitle, p);
			inlinearLayout.addView(RG_Gender, p);
			inlinearLayout.addView(CB_Preg, p);
			inlinearLayout.addView(tvage, p);
			inlinearLayout.addView(NP_Age, p);
			inlinearLayout.addView(BT_gosym, p);
			scrollView.addView(inlinearLayout);
			firstFrame.addView(scrollView);
			mainLayout.addView(firstFrame);
			setContentView(mainLayout);
			LoadSymptoms();
			LoadDiseaseAndMedinames();
			LoadWeights();
		}
		catch (Exception e)
		{
			ByteArrayOutputStream out = new ByteArrayOutputStream();
			PrintStream pinrtStream = new PrintStream(out);
			//e.printStackTrace()하면 System.out에 찍는데,
			// 출력할 PrintStream을 생성해서 건네 준다
			e.printStackTrace(pinrtStream);
			String stackTraceString = out.toString(); // 찍은 값을 가져오고.
			Toast.makeText(this, stackTraceString, 50).show();//보여 준다
		} 	
		//setContentView(R.layout.main);
		//mainLayout = (LinearLayout)findViewById(R.id.mainLayout);
		//firstFrame=(FrameLayout) findViewById(R.id.firstFrame);
		//NP_Age=(NumberPicker) findViewById(R.id.NP_Age);
		//RB_Gender=(RadioButton) findViewById(R.id.RB_Male);
		//CB_Preg= (CheckBox) findViewById(R.id.CB_Preg);
		//BT_gosym = (Button)findViewById(R.id.BtnGoSym);
    }

	@Override
	protected void onDestroy()
	{
		// TODO: Implement this method
		super.onDestroy();
		finalize();
	}
	ArrayList<ArrayList<String>> symptomNames;
	ArrayList<String> kinds;
	//설정 파일을 읽어 동적으로 페이지를 생성하는 루틴
	private void LoadSymptoms() throws Exception
	{
		//File file  =  new File("Symptoms.txt");		//Root 디렉터리에 접근

		int i=0;
		symptomNames = new ArrayList<ArrayList<String>>();

		kinds = new ArrayList<String>();

		nextButtons = new ArrayList<Button>();
		try
		{
			BufferedReader br  =  new BufferedReader(new InputStreamReader(getResources().openRawResource(R.raw.symptoms), "euc-kr"));

			String line;
			String kind,sym;
			ArrayList<String> buf=null;
			while ((line = br.readLine()) != null)
			{
				buf = new ArrayList<String>();
				if (i % 2 == 0)
				{
					kind = line;
					kinds.add(kind);
					if (i != 0)
					{
						symptomNames.add(new ArrayList<String>(buf));
						buf.clear();
					}
				}
				else
				{
					StringTokenizer tokenizer=new StringTokenizer(line, " ");
					while (tokenizer.hasMoreTokens())
					{
						sym = tokenizer.nextToken(" ");	
						buf.add(sym);
					}
				}
				++i;
			}
			if (buf != null)
			{
				symptomNames.add(new ArrayList<String>(buf));
			}

			//buf.clear();

		}
		catch (IOException e)
		{
			Toast.makeText(this, e.toString() + System.getProperties().toString(), 50).show();
		}
		//이제 뷰 동적 생성
		nextButtons.add(BT_gosym);
		symptomTabFrames = new ArrayList<FrameLayout>();
		int sz=kinds.size();
		for (int j=0;j < sz;++j)
		{
			String symnam=kinds.get(j);
			TextView tv=new TextView(this);
			tv.setText(symnam);
			tv.setTextSize(20);
			FrameLayout frame=new FrameLayout(this);
			ScrollView scr=new ScrollView(this);
			GridLayout grid=new GridLayout(this);
			grid.setColumnCount(3);
			grid.setOrientation(grid.HORIZONTAL);
			GridLayout.LayoutParams par=new GridLayout.LayoutParams();
			GridLayout.Spec gspec=GridLayout.spec(0,3);
			par.columnSpec=gspec;
			grid.addView(tv,par);
//			CheckBox cb1=new CheckBox(this);
//			cb1.setEnabled(false);
//			cb1.setVisibility(View.INVISIBLE);
//			grid.addView(cb1);
//			CheckBox cb2=new CheckBox(this);
//			cb2.setEnabled(false);
//			cb2.setVisibility(View.INVISIBLE);
//			grid.addView(cb2);
			int ssz=symptomNames.get(j).size();
			Toast.makeText(this, new Integer(ssz).toString(), 1).show();
			for (int k=0;k < ssz;++k)
			{
				CheckBox cb=new CheckBox(this);
				cb.setText(symptomNames.get(j).get(k));
				cb.setChecked(false);
				grid.addView(cb);
			}
			Button button=new Button(this);
			if (j == sz - 1)
			{
				button.setText("결과 받기");
			}
			else
			{
				button.setText("다음");
			}
			button.setOnClickListener(this);
			nextButtons.add(button);
			grid.addView(button);
			scr.addView(grid);
			frame.addView(scr);
			frame.setVisibility(frame.GONE);
			mainLayout.addView(frame);
			symptomTabFrames.add(frame);
		}
	}
	//설정 파일을 읽어 동적으로 페이지를 생성하는 루틴
	ArrayList<String> diseaseNames;
	ArrayList<String> mediNames;
	private void LoadDiseaseAndMedinames() throws Exception
	{
		//File file  =  new File("Symptoms.txt");		//Root 디렉터리에 접근

		diseaseNames = new ArrayList<String>();
		try
		{
			BufferedReader br  =  new BufferedReader(new InputStreamReader(getResources().openRawResource(R.raw.diseases), "euc-kr"));

			String line,name;
			if((line = br.readLine()) != null)
			{
				StringTokenizer tokenizer=new StringTokenizer(line, " ");
				while (tokenizer.hasMoreTokens())
				{
					name = tokenizer.nextToken(" ");	
					diseaseNames.add(name);
				}
			}
		}
		catch (IOException e)
		{
			Toast.makeText(this, e.toString(), 50).show();
		}
		mediNames = new ArrayList<String>();
		try
		{
			BufferedReader br  =  new BufferedReader(new InputStreamReader(getResources().openRawResource(R.raw.drugs), "euc-kr"));

			String line,name;
			if((line = br.readLine()) != null)
			{
				StringTokenizer tokenizer=new StringTokenizer(line, " ");
				while (tokenizer.hasMoreTokens())
				{
					name = tokenizer.nextToken(" ");	
					mediNames.add(name);
				}
			}
		}
		catch (IOException e)
		{
			Toast.makeText(this, e.toString(), 50).show();
		}
	}
	
	//Weights를 로드한다.
	private void LoadWeights() throws Exception
	{
		//File file  =  new File("Symptoms.txt");		//Root 디렉터리에 접근

		//diseaseNames = new ArrayList<String>();
		try
		{
			BufferedReader br  =  new BufferedReader(new InputStreamReader(getResources().openRawResource(R.raw.weights), "UTF-8"));

			String line,name;
			if((line = br.readLine()) != null)
			{
				StringTokenizer tokenizer=new StringTokenizer(line, " ");
				while (tokenizer.hasMoreTokens())
				{
					name = tokenizer.nextToken(" ");	
					//diseaseNames.add(name);
				}
			}
		}
		catch (IOException e)
		{
			Toast.makeText(this, e.toString(), 50).show();
		}
		
	}
	private void Invoke()
	{
		try
		{
			//자료를 가공하여 Native로 보낸다.
			int siz=symptombytes.size();
			byte [] syms=new byte[siz];
			syms = toPrimitives( symptombytes);
			initData(male, preg, age, 50, syms);
			calcData();
			int disid1,disid2;
			disid1=0;
			disid2=12;
			int prob1=40;
			int prob2=20;
			int[] mediid1={1};
			int[] mediid2={0};
			disid1=getDisID(0);
			disid2=getDisID(1);
			prob1=getProb(0);
			prob2=getProb(1);
			mediid1=getDrugID(0);
			mediid2=getDrugID(1);
			String medi1=mediIDsToString(mediid1);
			String medi2=mediIDsToString(mediid2);
			String DiseaseOne=diseaseNames.get(disid1);
			String DiseaseTwo=diseaseNames.get(disid2);
			Intent intent=new Intent(this, ShowActivity.class);
			intent.putExtra("com.kyunggi.medinology.diseaseone.MESSAGE",new Integer(prob1).toString()+"%확률로 "+DiseaseOne+"이며 치료제는 "+medi1+"입니다.");
			intent.putExtra("com.kyunggi.medinology.diseasetwo.MESSAGE",new Integer(prob2).toString()+"%확률로 "+DiseaseTwo+"이며 치료제는 "+medi2+"입니다.");
			startActivity(intent);
		}
		catch (Exception e)
		{
			ByteArrayOutputStream out = new ByteArrayOutputStream();
			PrintStream pinrtStream = new PrintStream(out);
			//e.printStackTrace()하면 System.out에 찍는데,
			// 출력할 PrintStream을 생성해서 건네 준다
			e.printStackTrace(pinrtStream);
			String stackTraceString = out.toString(); // 찍은 값을 가져오고.
			Toast.makeText(this, stackTraceString, 50).show();//보여 준다
		}
	}

	private native void initData(boolean male, boolean preg, int age, int weight, byte[]symptoms);
	private native void calcData();
	private native int getDisID(int n);
	private native int getProb(int n);
	private native int[] getDrugID(int n);
	private native void initWeights(float [] weights,int dim);
	private native void finalizeNative();
	
    /* this is used to load the 'hello-jni' library on application
     * startup. The library has already been unpacked into
     * /data/data/com.example.hellojni/lib/libhello-jni.so at
     * installation time by the package manager.
     */
	 
	 private String mediIDsToString(int[] ids)
	 {
		 int len=ids.length;
		 String ret=new String();
		 for(int i=0;i<len;++i)
		 {
			 ret+=mediNames.get(ids[i])+" ";
		 }
		 return ret;
	 }
	byte[] toPrimitives(ArrayList<Byte> oBytes)
	{
		byte[] bytes = new byte[oBytes.size()];

		for (int i = 0; i < oBytes.size(); i++)
		{
			bytes[i] = oBytes.get(i);
		}

		return bytes;
	}

	public String ReadTextAssets(String strFileName) {
        String text = null;
        try {
            InputStream is = getAssets().open(strFileName);
            int size = is.available();
            byte[] buffer = new byte[size];
            is.read(buffer);
            is.close();

            text = new String(buffer);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        return text;
    }

    public boolean WriteTextFile(String strFileName, String strBuf) {
        try {
            File file = getFileStreamPath(strFileName);
            FileOutputStream fos = new FileOutputStream(file);
            Writer out = new OutputStreamWriter(fos, "UTF-8");
            out.write(strBuf);
            out.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        return true;
    }
	//Fixme
    public String ReadTextFile(String strFileName) {
        String text = null;
        try {
            File file = getFileStreamPath(strFileName);
            FileInputStream fis = new FileInputStream(file);
         //   Reader in = new InputStreamReader(fis);
			Scanner s = new Scanner(fis).useDelimiter("\\A");
			text = s.hasNext() ? s.next() : "";
          //  int size = fis.available();
		//	CharBuffer buffer=CharBuffer.allocate(200);
       //     in.read(buffer);
       //     in.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        return text;
    }


    static {
		System.loadLibrary("hello-jni");
    }
	//	private void LoadSymptoms()
//	{
//		File file  =  new File("Symptoms.txt");
//		int i=0;
//		try
//		{
//			BufferedReader br  =  new BufferedReader(new InputStreamReader(new FileInputStream(file), "euc-kr"));
//
//			String line;
//			String kind,sym;
//			FrameLayout framelayout=(FrameLayout) null;
//			GridLayout gridlayout=(GridLayout)null;
//			while((line = br.readLine()) != null)
//			{
//				if(i%2==0)
//				{
//					kind=line;
//					
//					if(i!=0)
//					{		
//						Button nextButton=new Button(this);
//						nextButton.setText("next");
//						gridlayout.addView(nextButton);
//						framelayout=new FrameLayout(this);
//						framelayout.addView(gridlayout);
//						framelayout.setVisibility(framelayout.INVISIBLE);
//						mainLayout.addView(framelayout);
//					}	
//					gridlayout=new GridLayout(this);
//					gridlayout.setOrientation(gridlayout.VERTICAL);
//					TextView tv=new TextView(this);
//					tv.setText(kind);
//					gridlayout.addView(tv);
//				}
//				else
//				{
//					StringTokenizer tokenizer=new StringTokenizer(line);
//					while(tokenizer.hasMoreTokens())
//					{
//						sym=tokenizer.nextToken(" ");
//						CheckBox checkbox=new CheckBox(this);
//						checkbox.setText(sym);
//						gridlayout.addView(checkbox);
//					}
//				}
//				++i;
//			}
//			framelayout=new FrameLayout(this);
//			framelayout.addView(gridlayout);
//			framelayout.setVisibility(framelayout.INVISIBLE);
//			mainLayout.addView(framelayout);
//		}
//		catch (IOException e)
//		{
//			Toast.makeText(this,e.toString(),10).show();
//		}
//
//	}
//	
}
