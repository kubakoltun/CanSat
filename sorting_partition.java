public class sorting_partition {  
    public static int[] sort(int[] data) {     
        int last = data[data.length-1];    
        int ll = data.length-1;     
        int ni = 0;    
        int[] sorted = new int[data.length];  
        
        for (int i = 0; i < data.length; i++) {    
            if (data[i] < last) {     
                sorted[ni] = data[i];     
                ni++;       
            }       
            else if (data[i] > last) {        
                sorted[ll] = data[i];      
                ll--;     
            } else {       
                sorted[ni] = data[i]; 
            }    
        }    
        
        return sorted;  
    }  
    
    public static void main(String[] args) {  
        int[] sortedOut = new int[] {1, 8, 7, 2, 4, 6, 10, 5};     
        int[] sourtedoutput = sort(sortedOut);
        
        for (int i : sourtedoutput) {
            System.out.print(i + " ");
        }  
    }
}
