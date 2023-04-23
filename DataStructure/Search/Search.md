## 탐색의 종류

- 순차 탐색
    - 차례대로 하나씩 탐색하는것
    
    ```cpp
    for (int i = 0; i < n; i++)
    {
    		if (arr[i] == target)
    		{
    				result = i + 1;
    				break;
    		}
    }
    ```
    
- 이진 탐색
    - 이미 정렬 되어있을때 반으로 나누어 클때는 큰쪽값 작을때는 작은쪽 값을 계산하면서 탐색을 하는 방식이다
    
    ```cpp
    int mid;
       
    while(start <= end) 
    {
        mid = (start + end) / 2;
        if(target == arr[mid]) 
    		{
             return mid;
        } 
    		else if(target < arr[mid]) 
    		{
             end = mid - 1;
        } 
    		else 
    		{
             start = mid + 1;
        }
    }
    ```
    

## 탐색과 정렬과의 관계

탐색을 할때 정렬이 되어있으면 탐색이 더 빠르기도 하다.

하지만 탐색이 되어있으면 데이터 추가관점에서는 정렬이 안되어있는게 빠르다
