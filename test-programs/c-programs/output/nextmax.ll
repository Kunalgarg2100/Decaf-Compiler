; ModuleID = '../nextmax.c'
source_filename = "../nextmax.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@arr = common global [100 x i32] zeroinitializer, align 16
@.str = private unnamed_addr constant [4 x i8] c"%d \00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.2 = private unnamed_addr constant [14 x i8] c"Invalid Input\00", align 1
@.str.3 = private unnamed_addr constant [26 x i8] c"No second largest element\00", align 1
@.str.4 = private unnamed_addr constant [29 x i8] c"Second Largest element is %d\00", align 1

; Function Attrs: noinline nounwind optnone
define void @initialize(i32 %n) #0 {
  %n.addr = alloca i32, align 4
  %i = alloca i32, align 4
  %i1 = alloca i32, align 4
  %i2 = alloca i32, align 4
  store i32 %n, i32* %n.addr, align 4
  store i32 0, i32* %i1, align 4
  br label %1

; <label>:1:                                      ; preds = %8, %0
  %2 = load i32, i32* %i1, align 4
  %3 = load i32, i32* %n.addr, align 4
  %cmp = icmp slt i32 %2, %3
  br i1 %cmp, label %4, label %10

; <label>:4:                                      ; preds = %1
  %5 = load i32, i32* %n.addr, align 4
  %6 = load i32, i32* %i1, align 4
  %sub = sub nsw i32 %5, %6
  %7 = load i32, i32* %i1, align 4
  %idxprom = sext i32 %7 to i64
  %arrayidx = getelementptr inbounds [100 x i32], [100 x i32]* @arr, i64 0, i64 %idxprom
  store i32 %sub, i32* %arrayidx, align 4
  br label %8

; <label>:8:                                      ; preds = %4
  %9 = load i32, i32* %i1, align 4
  %inc = add nsw i32 %9, 1
  store i32 %inc, i32* %i1, align 4
  br label %1

; <label>:10:                                     ; preds = %1
  store i32 0, i32* %i2, align 4
  br label %11

; <label>:11:                                     ; preds = %17, %10
  %12 = load i32, i32* %i2, align 4
  %13 = load i32, i32* %n.addr, align 4
  %cmp3 = icmp slt i32 %12, %13
  br i1 %cmp3, label %14, label %19

; <label>:14:                                     ; preds = %11
  %15 = load i32, i32* %i2, align 4
  %idxprom4 = sext i32 %15 to i64
  %arrayidx5 = getelementptr inbounds [100 x i32], [100 x i32]* @arr, i64 0, i64 %idxprom4
  %16 = load i32, i32* %arrayidx5, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %16)
  br label %17

; <label>:17:                                     ; preds = %14
  %18 = load i32, i32* %i2, align 4
  %inc6 = add nsw i32 %18, 1
  store i32 %inc6, i32* %i2, align 4
  br label %11

; <label>:19:                                     ; preds = %11
  %call7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0))
  ret void
}

declare i32 @printf(i8*, ...) #1

; Function Attrs: noinline nounwind optnone
define void @nextMax(i32 %n) #0 {
  %n.addr = alloca i32, align 4
  %max1 = alloca i32, align 4
  %max2 = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 %n, i32* %n.addr, align 4
  %1 = load i32, i32* %n.addr, align 4
  %cmp = icmp slt i32 %1, 2
  br i1 %cmp, label %2, label %3

; <label>:2:                                      ; preds = %0
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i32 0, i32 0))
  br label %3

; <label>:3:                                      ; preds = %2, %0
  store i32 -1, i32* %max1, align 4
  store i32 -1, i32* %max2, align 4
  store i32 0, i32* %i, align 4
  br label %4

; <label>:4:                                      ; preds = %29, %3
  %5 = load i32, i32* %i, align 4
  %6 = load i32, i32* %n.addr, align 4
  %cmp1 = icmp slt i32 %5, %6
  br i1 %cmp1, label %7, label %31

; <label>:7:                                      ; preds = %4
  %8 = load i32, i32* %i, align 4
  %idxprom = sext i32 %8 to i64
  %arrayidx = getelementptr inbounds [100 x i32], [100 x i32]* @arr, i64 0, i64 %idxprom
  %9 = load i32, i32* %arrayidx, align 4
  %10 = load i32, i32* %max1, align 4
  %cmp2 = icmp sgt i32 %9, %10
  br i1 %cmp2, label %11, label %15

; <label>:11:                                     ; preds = %7
  %12 = load i32, i32* %max1, align 4
  store i32 %12, i32* %max2, align 4
  %13 = load i32, i32* %i, align 4
  %idxprom3 = sext i32 %13 to i64
  %arrayidx4 = getelementptr inbounds [100 x i32], [100 x i32]* @arr, i64 0, i64 %idxprom3
  %14 = load i32, i32* %arrayidx4, align 4
  store i32 %14, i32* %max1, align 4
  br label %28

; <label>:15:                                     ; preds = %7
  %16 = load i32, i32* %i, align 4
  %idxprom5 = sext i32 %16 to i64
  %arrayidx6 = getelementptr inbounds [100 x i32], [100 x i32]* @arr, i64 0, i64 %idxprom5
  %17 = load i32, i32* %arrayidx6, align 4
  %18 = load i32, i32* %max2, align 4
  %cmp7 = icmp sgt i32 %17, %18
  br i1 %cmp7, label %19, label %27

; <label>:19:                                     ; preds = %15
  %20 = load i32, i32* %i, align 4
  %idxprom8 = sext i32 %20 to i64
  %arrayidx9 = getelementptr inbounds [100 x i32], [100 x i32]* @arr, i64 0, i64 %idxprom8
  %21 = load i32, i32* %arrayidx9, align 4
  %22 = load i32, i32* %max1, align 4
  %cmp10 = icmp ne i32 %21, %22
  br i1 %cmp10, label %23, label %26

; <label>:23:                                     ; preds = %19
  %24 = load i32, i32* %i, align 4
  %idxprom11 = sext i32 %24 to i64
  %arrayidx12 = getelementptr inbounds [100 x i32], [100 x i32]* @arr, i64 0, i64 %idxprom11
  %25 = load i32, i32* %arrayidx12, align 4
  store i32 %25, i32* %max2, align 4
  br label %26

; <label>:26:                                     ; preds = %23, %19
  br label %27

; <label>:27:                                     ; preds = %26, %15
  br label %28

; <label>:28:                                     ; preds = %27, %11
  br label %29

; <label>:29:                                     ; preds = %28
  %30 = load i32, i32* %i, align 4
  %inc = add nsw i32 %30, 1
  store i32 %inc, i32* %i, align 4
  br label %4

; <label>:31:                                     ; preds = %4
  %32 = load i32, i32* %max2, align 4
  %cmp13 = icmp eq i32 %32, -1
  br i1 %cmp13, label %33, label %34

; <label>:33:                                     ; preds = %31
  %call14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.3, i32 0, i32 0))
  br label %36

; <label>:34:                                     ; preds = %31
  %35 = load i32, i32* %max2, align 4
  %call15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.4, i32 0, i32 0), i32 %35)
  br label %36

; <label>:36:                                     ; preds = %34, %33
  ret void
}

; Function Attrs: noinline nounwind optnone
define void @main() #0 {
  %n = alloca i32, align 4
  store i32 100, i32* %n, align 4
  %1 = load i32, i32* %n, align 4
  call void @initialize(i32 %1)
  %2 = load i32, i32* %n, align 4
  call void @nextMax(i32 %2)
  ret void
}

attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.1-svn334776-1~exp1~20180919141756.113 (branches/release_60)"}
