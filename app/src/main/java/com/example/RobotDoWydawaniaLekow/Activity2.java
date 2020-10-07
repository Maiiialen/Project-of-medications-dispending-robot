package com.example.RobotDoWydawaniaLekow;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.util.ArrayList;

public class Activity2 extends AppCompatActivity {
    ListView listView1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_2);

        getSupportActionBar().setTitle("Wszystkie alarmy");
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        listView1 = (ListView) findViewById(R.id.listview1);
        ArrayList<String> arrayList = new ArrayList<>();
        arrayList.add("one");
        arrayList.add("two");
        arrayList.add("three");
        arrayList.add("one");
        arrayList.add("two");
        arrayList.add("three");
        arrayList.add("one");
        arrayList.add("two");
        arrayList.add("three");
        arrayList.add("one");
        arrayList.add("two");
        arrayList.add("three");
        arrayList.add("one");
        arrayList.add("two");
        arrayList.add("three");
        arrayList.add("one");
        arrayList.add("two");
        arrayList.add("three");
        arrayList.add("one");
        arrayList.add("two");
        arrayList.add("three");
        arrayList.add("one");
        arrayList.add("two");
        arrayList.add("three");
        arrayList.add("one");
        arrayList.add("two");
        arrayList.add("three");
        arrayList.add("one");
        arrayList.add("two");
        arrayList.add("three");

        ArrayAdapter arrayAdapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, arrayList);

        listView1.setAdapter(arrayAdapter);
    }
}