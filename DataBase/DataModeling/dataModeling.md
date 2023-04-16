## 데이터 베이스의 생명주기
1. 요구사항 수집 및 분석 - 사용자들의 요구사항을 듣고 분석하여 데이터베이스 구축 범위를 정함
2. 설계 - 분석된 요구사항을 기초로  설계를 한다
3. 구현 - 설계단계에서 생성한 스키마를 실제 DBMS에 적용하여 테이블 및 관련 객체를 만들고 서비스를 제공
4. 운영
5. 감시 및 개선

## 설계단계에서의 3가지 모델링
- 개념적 모델링 : 개체와 개체들 간의 관계에서 ER다이어 그램을 만드는 과정
<img width="374" alt="개념적 모델링의 예시" src="https://user-images.githubusercontent.com/59678097/232308405-24b0a1e7-5f4d-4d23-b4ee-a14ab41d8b45.png">
- 논리적 모델링 : ER다이어그램을 사용하여 관계스키마 모델을 만드는과정 
- <p align="center">
  <img src="[논리적 모델링의 예시](https://user-images.githubusercontent.com/59678097/232308549-d0e946aa-7589-4bd5-99cd-7231f17e93d9.png)">
</p>
- 물리적 모델링 : 관계 스키마 모델의 물리적 구조를 정의하고 구현하는 과정
- <img width="315" alt="물리적 모델링의 예시" src="https://user-images.githubusercontent.com/59678097/232308403-fb80ec77-9f4c-4796-a5b3-267b798e5bdb.png">