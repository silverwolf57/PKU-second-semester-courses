import pandas as pd

file_name = "finance.xlsx"
df = pd.read_excel(file_name, sheet_name='Sheet1')
df['日期'] = pd.to_datetime(df['日期'])
daily_sales = df.groupby('日期')['交易额'].sum().astype(int).reset_index()
lowest_three = daily_sales.sort_values(by='交易额', ascending=True).head(3)
for _, row in lowest_three.iterrows():
    date_str = row['日期'].strftime('%Y-%m-%d')
    total_sales = row['交易额']
    day_of_week = row['日期'].strftime('%A')  
    print(f"{date_str} {total_sales} {day_of_week}")