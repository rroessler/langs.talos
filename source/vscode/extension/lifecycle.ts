/// Node Modules
import { performance } from 'node:perf_hooks';

/// Talos Modules
import { Decorator, Dependency, Disposable, Inversify } from '@/talos/utilities';

/// Package Modules
import { Context } from './context';
import { Service } from './service';
import { Contribution } from './contribution';

/** Extension Lifecycle. */
@Inversify.injectable()
@Decorator.Class.Rename('Extension.Service')
export class Lifecycle extends Disposable implements Service {
    //  PROPERTIES  //

    /** The underlying extension API. */
    @Inversify.inject(Context) protected readonly m_context: Context;

    /** Extension Contributions Provider. */
    @Dependency.inject(Contribution) protected readonly m_contributions: Dependency<Contribution>;

    //  LIFECYCLE METHODS  //

    /** Gets the underlying context. */
    context() {
        return this.m_context;
    }

    /** Handles activating the lifecycle. */
    async activate() {
        // pre-push this instance as disposable now
        this.m_context.subscriptions.push(this);

        // configure and activate all the available extension
        const contributions = this.m_contributions.get();

        // attempt configuring and activating the contributions
        await this.m_apply('configure', contributions);
        await this.m_apply('activate', contributions);
    }

    /** Handles disposing of the lifecycle. */
    dispose() {
        for (const contribution of this.m_contributions) contribution.dispose?.();
    }

    //  PRIVATE METHODS  //

    /**
     * Allows measuring the total time contributions take.
     * @param action                    Action to measure.
     * @param contributions             Contributions list.
     */
    private async m_apply<K extends Contribution.Action>(action: K, contributions: readonly Contribution[]) {
        const elapsed = await Promise.all(contributions.map((contribution) => this.m_measure(action, contribution)));
        console.info(`Extension.Service.${action} took ${elapsed.reduce((acc, value) => acc + value, 0)} ms`);
    }

    /**
     * Measures a single contributions action.
     * @param action                    Action to measure.
     * @param contribution              Contribution instance.
     */
    private async m_measure<K extends Contribution.Action>(action: K, contribution: Contribution): Promise<number> {
        // ensure that we have a valid method
        const method = contribution[action];
        if (typeof method === 'undefined') return 0;

        const start = performance.now();
        await method.call(contribution);
        const elapsed = performance.now() - start;

        // show a log about the performance being taken now
        console.debug(`${contribution.constructor.name}.${action} took ${elapsed} ms`);

        // return the total elapsed time now
        return elapsed;
    }
}
