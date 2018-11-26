; ModuleID = '../ifelse.c'
source_filename = "../ifelse.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [5 x i8] c"123\0A\00", align 1
@.str.1 = private unnamed_addr constant [5 x i8] c"223\0A\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@n = common global i32 0, align 4
@sum = common global i32 0, align 4
@k = common global [5 x i32] zeroinitializer, align 16
@p = common global i32 0, align 4

; Function Attrs: noinline nounwind optnone
define i32 @fun(i32 %n, i32 %m) #0 {
  %retval = alloca i32, align 4
  %n.addr = alloca i32, align 4
  %m.addr = alloca i32, align 4
  store i32 %n, i32* %n.addr, align 4
  store i32 %m, i32* %m.addr, align 4
  %1 = load i32, i32* %retval, align 4
  ret i32 %1
}

; Function Attrs: noinline nounwind optnone
define void @main() #0 {
  %l = alloca i32, align 4
  %m = alloca i32, align 4
  store i32 6, i32* %m, align 4
  %1 = load i32, i32* %m, align 4
  %cmp = icmp sgt i32 %1, 5
  br i1 %cmp, label %2, label %7

; <label>:2:                                      ; preds = %0
  store i32 3, i32* %m, align 4
  %3 = load i32, i32* %m, align 4
  %cmp1 = icmp sgt i32 %3, 4
  br i1 %cmp1, label %4, label %5

; <label>:4:                                      ; preds = %2
  store i32 1, i32* %m, align 4
  br label %6

; <label>:5:                                      ; preds = %2
  store i32 12, i32* %m, align 4
  br label %6

; <label>:6:                                      ; preds = %5, %4
  br label %8

; <label>:7:                                      ; preds = %0
  store i32 2, i32* %m, align 4
  br label %8

; <label>:8:                                      ; preds = %7, %6
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0))
  %call2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0))
  %call3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i32 5)
  %9 = load i32, i32* %m, align 4
  %call4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i32 %9)
  ret void
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.1-svn334776-1~exp1~20180919141756.113 (branches/release_60)"}
