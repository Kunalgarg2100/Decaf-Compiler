; ModuleID = '../bubble.c'
source_filename = "../bubble.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@inp = common global [100 x i32] zeroinitializer, align 16
@.str = private unnamed_addr constant [4 x i8] c"%d \00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

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
  %arrayidx = getelementptr inbounds [100 x i32], [100 x i32]* @inp, i64 0, i64 %idxprom
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
  %arrayidx5 = getelementptr inbounds [100 x i32], [100 x i32]* @inp, i64 0, i64 %idxprom4
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
define void @bubblesort(i32 %n) #0 {
  %n.addr = alloca i32, align 4
  %i = alloca i32, align 4
  %tmp = alloca i32, align 4
  %i1 = alloca i32, align 4
  %j = alloca i32, align 4
  %i18 = alloca i32, align 4
  store i32 %n, i32* %n.addr, align 4
  store i32 0, i32* %i1, align 4
  br label %1

; <label>:1:                                      ; preds = %26, %0
  %2 = load i32, i32* %i1, align 4
  %3 = load i32, i32* %n.addr, align 4
  %cmp = icmp slt i32 %2, %3
  br i1 %cmp, label %4, label %28

; <label>:4:                                      ; preds = %1
  store i32 0, i32* %j, align 4
  br label %5

; <label>:5:                                      ; preds = %23, %4
  %6 = load i32, i32* %i1, align 4
  %7 = load i32, i32* %n.addr, align 4
  %8 = load i32, i32* %i1, align 4
  %sub = sub nsw i32 %7, %8
  %sub2 = sub nsw i32 %sub, 1
  %cmp3 = icmp slt i32 %6, %sub2
  br i1 %cmp3, label %9, label %25

; <label>:9:                                      ; preds = %5
  %10 = load i32, i32* %j, align 4
  %idxprom = sext i32 %10 to i64
  %arrayidx = getelementptr inbounds [100 x i32], [100 x i32]* @inp, i64 0, i64 %idxprom
  %11 = load i32, i32* %arrayidx, align 4
  %12 = load i32, i32* %j, align 4
  %add = add nsw i32 %12, 1
  %idxprom4 = sext i32 %add to i64
  %arrayidx5 = getelementptr inbounds [100 x i32], [100 x i32]* @inp, i64 0, i64 %idxprom4
  %13 = load i32, i32* %arrayidx5, align 4
  %cmp6 = icmp sgt i32 %11, %13
  br i1 %cmp6, label %14, label %22

; <label>:14:                                     ; preds = %9
  %15 = load i32, i32* %j, align 4
  %idxprom7 = sext i32 %15 to i64
  %arrayidx8 = getelementptr inbounds [100 x i32], [100 x i32]* @inp, i64 0, i64 %idxprom7
  %16 = load i32, i32* %arrayidx8, align 4
  store i32 %16, i32* %tmp, align 4
  %17 = load i32, i32* %j, align 4
  %add9 = add nsw i32 %17, 1
  %idxprom10 = sext i32 %add9 to i64
  %arrayidx11 = getelementptr inbounds [100 x i32], [100 x i32]* @inp, i64 0, i64 %idxprom10
  %18 = load i32, i32* %arrayidx11, align 4
  %19 = load i32, i32* %j, align 4
  %idxprom12 = sext i32 %19 to i64
  %arrayidx13 = getelementptr inbounds [100 x i32], [100 x i32]* @inp, i64 0, i64 %idxprom12
  store i32 %18, i32* %arrayidx13, align 4
  %20 = load i32, i32* %tmp, align 4
  %21 = load i32, i32* %j, align 4
  %add14 = add nsw i32 %21, 1
  %idxprom15 = sext i32 %add14 to i64
  %arrayidx16 = getelementptr inbounds [100 x i32], [100 x i32]* @inp, i64 0, i64 %idxprom15
  store i32 %20, i32* %arrayidx16, align 4
  br label %22

; <label>:22:                                     ; preds = %14, %9
  br label %23

; <label>:23:                                     ; preds = %22
  %24 = load i32, i32* %j, align 4
  %inc = add nsw i32 %24, 1
  store i32 %inc, i32* %j, align 4
  br label %5

; <label>:25:                                     ; preds = %5
  br label %26

; <label>:26:                                     ; preds = %25
  %27 = load i32, i32* %i1, align 4
  %inc17 = add nsw i32 %27, 1
  store i32 %inc17, i32* %i1, align 4
  br label %1

; <label>:28:                                     ; preds = %1
  store i32 0, i32* %i18, align 4
  br label %29

; <label>:29:                                     ; preds = %35, %28
  %30 = load i32, i32* %i18, align 4
  %31 = load i32, i32* %n.addr, align 4
  %cmp19 = icmp slt i32 %30, %31
  br i1 %cmp19, label %32, label %37

; <label>:32:                                     ; preds = %29
  %33 = load i32, i32* %i18, align 4
  %idxprom20 = sext i32 %33 to i64
  %arrayidx21 = getelementptr inbounds [100 x i32], [100 x i32]* @inp, i64 0, i64 %idxprom20
  %34 = load i32, i32* %arrayidx21, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %34)
  br label %35

; <label>:35:                                     ; preds = %32
  %36 = load i32, i32* %i18, align 4
  %inc22 = add nsw i32 %36, 1
  store i32 %inc22, i32* %i18, align 4
  br label %29

; <label>:37:                                     ; preds = %29
  %call23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0))
  ret void
}

; Function Attrs: noinline nounwind optnone
define void @main() #0 {
  %n = alloca i32, align 4
  store i32 10, i32* %n, align 4
  %1 = load i32, i32* %n, align 4
  call void @initialize(i32 %1)
  %2 = load i32, i32* %n, align 4
  call void @bubblesort(i32 %2)
  ret void
}

attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.1-svn334776-1~exp1~20180919141756.113 (branches/release_60)"}
