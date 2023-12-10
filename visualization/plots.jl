using Plots
using Tables
using CSV

lcg = CSV.File("visualization/data/lcg.csv") |>  Tables.matrix

begin
    
    p = histogram(lcg[:,2],
                    bins=30,
                    xlabel="Value",
                    ylabel="Frequency",
                    title="Histogram",
                    label = "Linear congruent generator"
        )
end

norm2d = CSV.File("visualization/data/norm2d_deg.csv") |>  Tables.matrix

begin
    scatter(norm2d[:,1],norm2d[:,2])
end


begin
    histogram2d(norm2d[:,1],norm2d[:,2], bins=50)
end


beta = CSV.File("visualization/data/beta.csv") |>  Tables.matrix

begin
    scatter(beta[:,1], beta[:,2])
end


beta_sampled = CSV.File("visualization/data/beta_sampling.csv") |>  Tables.matrix

begin

    xx = beta[:, 1]
    yy = beta[:, 2]
    p_star = maximum(yy)

    (acc_samples, acc_u) = (beta_sampled[:, 1],  beta_sampled[:, 2]);

    plot1 = plot(xx, yy, color=:black, linewidth=2, label="");
    plot!(plot1, [0, 1], [p_star, p_star], color=:red, linewidth=2, linestyle=:dash, label="");
    scatter!(plot1, acc_samples, acc_u, color=:red, markersize=2, label="");
    xlims!(plot1, 0, 1);
    ylims!(plot1, 0, 2.8);

    # Second subplot
    plot2 = plot()
    plot!(plot2, xx, yy, color=:red, linewidth=2, label="");
    histogram!(plot2, acc_samples, bins=100, normalized=true, color=:black, alpha=0.7, label="", opacity = 0.4);
    xlims!(plot2, 0, 1);

    plot(plot1, plot2, layout=(1, 2))

end


onlinestats = CSV.File("visualization/data/onlinestat.csv") |>  Tables.matrix
begin
    signal =  onlinestats[:,1]
    ma = onlinestats[:,2]
    var = onlinestats[:,3]

    plot(signal, label = "signal")
    plot!(ma, label = "ma")
    plot!(sqrt.(var) , label = "std")
end