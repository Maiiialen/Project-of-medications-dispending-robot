package com.example.RobotDoWydawaniaLekow;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {
    DatabaseReference reff;
    Wyswietlanie_danych wys;
    ListView listView;
    ArrayList<String> arrayList = new ArrayList<>();
    //Date currentTime = Calendar.getInstance().getTime();
    SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy", Locale.getDefault());
    String currentDateandTime = sdf.format(new Date());
    String dzien;
    String miesiac;
    String rok;
    String godziny;
    String minuty;
    Long ilosc;
    String temp;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getSupportActionBar().setTitle("Strona główna");

        /*listView = (ListView) findViewById(R.id.listview);
        ArrayList<String> arrayList = new ArrayList<>();
        arrayList.add("one");
        arrayList.add("two");
        arrayList.add("three");
        arrayList.add(currentDateandTime);
        ArrayAdapter arrayAdapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, arrayList);
        listView.setAdapter(arrayAdapter);*/

        /*// łączenie z bazą danych
        wys = new Wyswietlanie_danych();
        reff = FirebaseDatabase.getInstance().getReference().child("Dane").child("dane1");
        // przesłanie danego ustawienia
        int dzien = Integer.parseInt("5".trim());
        wys.setDzien(dzien);
        reff.setValue(wys);
        int miesiac = Integer.parseInt("9".trim());
        wys.setMiesiac(miesiac);
        reff.setValue(wys);
        int rok = Integer.parseInt("2020".trim());
        wys.setRok(rok);
        reff.setValue(wys);
        int godzina = Integer.parseInt("15".trim());
        wys.setGodziny(godzina);
        reff.setValue(wys);
        int minuty = Integer.parseInt("18".trim());
        wys.setMinuty(minuty);
        reff.setValue(wys);*/

        reff = FirebaseDatabase.getInstance().getReference().child("Dane");
        reff.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                ilosc = snapshot.getChildrenCount();
                for(long i = ilosc.longValue(); i > ilosc-3; --i){
                    temp = "" + i;
                    dzien = snapshot.child("dane" + temp).child("dzien").getValue().toString();
                    miesiac = snapshot.child("dane" + temp).child("miesiac").getValue().toString();
                    rok = snapshot.child("dane" + temp).child("rok").getValue().toString();
                    godziny = snapshot.child("dane" + temp).child("godziny").getValue().toString();
                    minuty = snapshot.child("dane" + temp).child("minuty").getValue().toString();
                    if(miesiac.length()==1)
                        miesiac = "0"+miesiac;
                    if(minuty.length()==1)
                        minuty = "0"+minuty;
                    dodajNaListe();
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        if(item.getItemId() == R.id.settings){
            openActivity();
        }
        if(item.getItemId() == R.id.full_list){
            openActivity1();
        }
        return super.onOptionsItemSelected(item);
    }

    public void openActivity(){
        Intent intent = new Intent(this, Activity1.class);
        startActivity(intent);
    }

    public void openActivity1(){
        Intent intent = new Intent(this, Activity2.class);
        startActivity(intent);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.my_menu, menu);
        return true;
    }

    public void dodajNaListe() {
        listView = (ListView) findViewById(R.id.listview);
        arrayList.add(dzien+"."+miesiac+"."+rok+", "+godziny+":"+minuty);
        //Log.d("nanana", "-------------------------");
        ArrayAdapter arrayAdapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, arrayList);
        listView.setAdapter(arrayAdapter);
    }
}