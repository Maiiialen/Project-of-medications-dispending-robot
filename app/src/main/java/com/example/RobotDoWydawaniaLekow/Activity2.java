package com.example.RobotDoWydawaniaLekow;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;

public class Activity2 extends AppCompatActivity {
    ListView listView1;
    DatabaseReference reff;
    String liczba;
    Boolean test = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_2);

        getSupportActionBar().setTitle("Wszystkie alarmy");
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        reff = FirebaseDatabase.getInstance().getReference().child("Przesyl_ustawien");
        reff.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                liczba = snapshot.child("ilosc").getValue().toString();
                test = true;
                dodajNaListe();
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

    }

    public void dodajNaListe() {
        listView1 = (ListView) findViewById(R.id.listview1);
        ArrayList<String> arrayList = new ArrayList<>();
        arrayList.add(0, liczba);
        ArrayAdapter arrayAdapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, arrayList);
        listView1.setAdapter(arrayAdapter);
    }
}