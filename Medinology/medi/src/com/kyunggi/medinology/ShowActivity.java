package com.kyunggi.medinology;

import android.app.*;
import android.content.*;
import android.os.*;
import android.widget.*;


public class ShowActivity extends Activity
{
	/** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {

        super.onCreate(savedInstanceState);
		setContentView(R.layout.showresult);
		// Get the message from the intent
        Intent intent = getIntent();
        String disease1 = intent.getStringExtra("com.kyunggi.medinology.diseaseone.MESSAGE");
		String disease2=  intent.getStringExtra("com.kyunggi.medinology.diseasetwo.MESSAGE");
        TextView disOneTextView = (TextView)findViewById(R.id.diseaseoneTextView);
        disOneTextView.setText(disease1);
		TextView disTwoTextView = (TextView)findViewById(R.id.diseasetwoTextView);
        disTwoTextView.setText(disease2);
		
	}
}
