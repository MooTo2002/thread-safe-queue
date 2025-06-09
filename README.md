# OS과제2 thread-safe-queue

## 학번 이름
- 이름: 이승준
- 학번: 20210550
- GitHub 링크: https://github.com/MooTo2002/thread-safe-queue
  
## 구현 내용
- enqueue
- dequeue
- range

## 테스트 환경
- Visual Studio 2022

## 제출 파일
- queue.cpp
- qtype.h
- url.txt

## 🛠 구현 기능 요약
- init(): 큐 초기화
- enqueue()
- dequque()
- range
- realse()
- thread-safe 처리
작업 일지

### ✔️ (6/5)
- qtype.h 기본 구조체 정의
- init()
- 첫 커밋 완료

### ✔️ (6/7)
- enqueue() 구현 (key 오름차순 정렬)

### ✔️ (6/8)
- dequeue() 구현
- range() 함수 구현
- main.cpp에서 전체 흐름 테스트

### ✔️ (6/9)
- 'std::mutex'를 활용한 thread-safe 완성
- 'release()' 구현
- 'iclone()'에 null 종료 포함
- 디버그 에러 및 이중 해제 문제 해결
