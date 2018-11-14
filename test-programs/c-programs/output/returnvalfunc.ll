; ModuleID = '../returnvalfuc.c'
source_filename = "../returnvalfuc.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"ans is %d\0A\00", align 1

; Function Attrs: noinline nounwind optnone
define i32 @num(i32 %a) #0 {
  %a.addr = alloca i32, align 4
  store i32 %a, i32* %a.addr, align 4
  %1 = load i32, i32* %a.addr, align 4
  ret i32 %1
}

; Function Attrs: noinline nounwind optnone
define i32 @func(i32 %n) #0 {
  %n.addr = alloca i32, align 4
  %sum = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 %n, i32* %n.addr, align 4
  store i32 0, i32* %sum, align 4
  store i32 1, i32* %i, align 4
  br label %1

; <label>:1:                                      ; preds = %7, %0
  %2 = load i32, i32* %i, align 4
  %3 = load i32, i32* %n.addr, align 4
  %cmp = icmp sle i32 %2, %3
  br i1 %cmp, label %4, label %9

; <label>:4:                                      ; preds = %1
  %5 = load i32, i32* %i, align 4
  %call = call i32 @num(i32 %5)
  %6 = load i32, i32* %sum, align 4
  %add = add nsw i32 %6, %call
  store i32 %add, i32* %sum, align 4
  br label %7

; <label>:7:                                      ; preds = %4
  %8 = load i32, i32* %i, align 4
  %inc = add nsw i32 %8, 1
  store i32 %inc, i32* %i, align 4
  br label %1

; <label>:9:                                      ; preds = %1
  %10 = load i32, i32* %sum, align 4
  ret i32 %10
}

; Function Attrs: noinline nounwind optnone
define void @main() #0 {
  %n = alloca i32, align 4
  %ans = alloca i32, align 4
  store i32 50, i32* %n, align 4
  %1 = load i32, i32* %n, align 4
  %call = call i32 @func(i32 %1)
  store i32 %call, i32* %ans, align 4
  %2 = load i32, i32* %ans, align 4
  %call1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str, i32 0, i32 0), i32 %2)
  ret void
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.1-svn334776-1~exp1~20180919141756.113 (branches/release_60)"}
