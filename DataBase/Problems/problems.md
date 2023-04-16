
### book 테이블
| bookid | bookname | publisher | price |
| --- | --- | --- | --- |
| 1 | 축구의 역사 | 굿스포츠 | 7000 |
| 2 | 축구아는 여자 | 나무수 | 13000 |
| 3 | 축구의 이해 | 대한미디어 | 22000 |
| 4 | 골프 바이블 | 대한미디어 | 35000 |
| 5 | 피겨 교본 | 굿스포츠 | 8000 |
| 6 | 역도 단계별기술 | 굿스포츠 | 6000 |
| 7 | 야구의 추억 | 이상미디어 | 20000 |
| 8 | 야구를 부탁해 | 이상미디어 | 13000 |
| 9 | 올림픽 이야기 | 삼성당 | 7500 |
| 10 | Olympic Champions | Pearson | 13000 |
### customer 테이블
| custid | pname | address | phone |
|--- | --- | --- | --- |
| 1 | 박지성 | 영국 맨체스타 | 000-5000-0001');
| 2 | 김연아 | 대한민국 서울 | 000-6000-0001');
| 3 | 장미란 | 대한민국 강원도 | 000-7000-0001');
| 4 | 추신수 | 미국 클리블랜드 | 000-8000-0001');
| 5 | 박세리 | 대한민국 대전 | NULL);
### orders 테이블
| orderid| custid | bookid | saleprice | orderdate |
| --- | --- | --- | --- | --- |
| 1 | 1 | 1 | 7000 | 2014-07-01 | 
| 2 | 1 | 3 | 21000 | 2014-07-03 | 
| 3 | 2 | 5 | 8000 | 2014-07-03 | 
| 4 | 3 | 6 | 6000 | 2014-07-04 | 
| 5 | 4 | 7 | 20000 | 2014-07-05 | 
| 6 | 1 | 2 | 12000 | 2014-07-07 | 
| 7 | 4 | 8 | 13000 | 2014-07-07 | 
| 8 | 3 | 10 | 12000 | 2014-07-08 | 
| 9 | 2 | 10 | 7000 | 2014-07-09 | 
| 10 | 3 | 8 | 13000 | 2014-07-10 | 

---

### 가격이 10000원 이상 20000이하인 도서를 검색하시오.

```sql
select * from book where price between 10000 and 20000;
```

### 도서 이름에 '축구'가 포함된 도서 이름과 출판사를 검색하시오

```sql
select bookname,publisher from book where bookname like '%축구%'
```

### 도서 이름의 왼쪽 두번째 위치에 '구'라는 문자열을 갖는 도서를 검색하시오. 

```sql
select * from book where bookname like '_구%';
```

### 도서를 가격의 내림차순으로 검색하시오. 만약 가격이 같다면 출판사의 오름차순으로 검색한다.

```sql
select * from book where order by price desc, publisher asc ;
```
### 김연아 고객이 주문한 도서의 총 판매액을 구하시오
```sql
select  sum(saleprice) from orders where  custid = select custid from customer where name = '김연아' ;
```
### 마당서점의 도서 판매 건수를 구하시오
```sql
select count(*) from orders;
```
### 고객별로 주문한 도서의 총 수량과 총 판매액을 구하시오
```sql
select custid, count(*), sum(saleprice) from orders group by custid;
```

### 고객의 이름과 고객이 주문한 도서의 판매가격을 검색하시오
```sql
select customer.name, orders.saleprice from orders,customer where orders.custid =customer.custid
```

### 고객별로 주문한 모든 도서의 총 판매액을 구하고, 고객별로 정렬하시오
```sql
select customer.name, sum(saleprice) from customer,orders where orders.custid =customer.custid  group by customer.name  order by customer.name ;
```
### 도서를 구매한 적이 있는 고객의 이름을 검색하시오
```sql
select customer.name from orders,customer where orders.custid = customer.custid group by orders.custid ;
```
### 대한미디어에서 출판한 도서를 구매한 고객의 이름을 보이시오
```sql
select customer.name from orders,customer,book where (book.publisher = '대한미디어')and (book.bookid = orders.orderid) and (orders.custid = customer.custid) group by customer.name;
```
### 주문이있는 고객의 이름과 주소를 보이시오
```sql
select customer.name,customer.address from customer,orders where customer.custid = orders.custid  group by custid;
```


### 각 고객이 구입한 책 중 가장 비싼 책
```sql
select customer.name,max(saleprice) from customer,orders where customer.custid = orders.cust id group by customer.custid ;
```
