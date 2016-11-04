package algorithms;

public class JavaSorting {

    private char[] charStr;
    private String string;

    public JavaSorting(String str) {
        charStr = str.toCharArray();
        string = str;
    }

    ///

    public void mergesort() {
        string = mergeSortHelper(string);
        charStr = string.toCharArray();
    }

    public String mergeSortHelper(String str) {
        if(str.length() == 1) return str;
        String firstHalf = str.substring(0, str.length()/2);
        String secondHalf = str.substring(str.length()/2, str.length());
        return mergeHelper(mergeSortHelper(firstHalf), mergeSortHelper(secondHalf));
    }

    private String mergeHelper(String s1, String s2) {
        StringBuilder charStr = new StringBuilder(s1.length()+s2.length());
        int s1C = 0;
        int s2C = 0;
        while(s1C < s1.length() && s2C < s2.length()) {
            if(s1.toLowerCase().charAt(s1C) <= s2.toLowerCase().charAt(s2C)) {
                charStr.insert(s1C+s2C,s1.charAt(s1C));
                s1C++;
            } else {
                charStr.insert(s1C+s2C, s2.charAt(s2C));
                s2C++;
            }
        }
        String sorted = new String(charStr);
        if(s1C < s1.length()) {
            sorted += s1.substring(s1C);
        }
        if(s2C < s2.length()) {
            sorted += s2.substring(s2C);
        }
        return sorted;
    }

    ///

    public void quicksort() {
        quicksortHelper(0, charStr.length-1);
        string = new String(charStr);
    }

    private void quicksortHelper(int low, int high) {
        int i = low;
        int j = high;
        char pivot = charStr[low + (high-low)/2];
        while(i<j) {
            while(charStr[i] < pivot) i++;
            while(charStr[j] > pivot) j--;
            if(i <= j) {
                swap(i, j);
                i++;
                j--;
            }
        }
        if(low < j)
            quicksortHelper(low, j);
        if(i < high)
            quicksortHelper(i, high);
    }

    private void swap(int i, int j) {
        char tmp = charStr[i];
        charStr[i] = charStr[j];
        charStr[j] = tmp;
    }

    ///

    public String getString() {
        return string;
    }

    public void setString(String str) {
        string = str;
        charStr = string.toCharArray();
    }

}
