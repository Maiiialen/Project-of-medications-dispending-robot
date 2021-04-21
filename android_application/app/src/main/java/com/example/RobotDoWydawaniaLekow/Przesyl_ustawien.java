package com.example.RobotDoWydawaniaLekow;

public class Przesyl_ustawien {
    private Integer liczba;
    private String godziny1;
    private String godziny2;
    private String godziny3;
    private Integer liczbaPozostalychDawek;

    public Przesyl_ustawien() {}

    public Integer getLiczba() {
        return liczba;
    }

    public void setLiczba(Integer liczba) {
        this.liczba = liczba;
    }

    public String getGodziny1() {
        return godziny1;
    }

    public void setGodziny1(String godziny1) {
        this.godziny1 = godziny1;
    }

    public String getGodziny2() {
        return godziny2;
    }

    public void setGodziny2(String godziny2) {
        this.godziny2 = godziny2;
    }

    public String getGodziny3() {
        return godziny3;
    }

    public void setGodziny3(String godziny3) {
        this.godziny3 = godziny3;
    }

    public Integer getLiczbaPozostalychDawek() {
        return liczbaPozostalychDawek;
    }

    public void setLiczbaPozostalychDawek(Integer liczbaPozostalychDawek) {
        this.liczbaPozostalychDawek = liczbaPozostalychDawek;
    }
}